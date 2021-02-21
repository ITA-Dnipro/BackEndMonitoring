#include "stdafx.h"

#include "CServiceConnectionHandler.h"
#include "CThreadPool.h"
#include "CAcceptor.h"
#include "CSocketWrapper.h"
#include "Log.h"
#include "GlobalVariable.h"
#include "CRequestHandler.h"

#include "CServiceHost.h"

CServiceHost::CServiceHost(int port, const std::string& ip_address,
    bool is_blocked, int socket_timeout, CEvent& event) :
	m_port(port), m_ip_address(ip_address), m_event(event),
	m_is_socket_blocked(is_blocked), m_socket_timeout(socket_timeout),
	m_is_host_initialized(false)
{ }

CServiceHost::~CServiceHost()
{
	PlatformUtils::FinalizeWinLibrary();
}

bool CServiceHost::Initialize(std::shared_ptr<CThreadPool> pool,
	CRequestHandler& json_data, const int connections)
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	if(m_is_host_initialized)
	{
		return true;
	}
	m_p_pool = std::move(pool);
	if (PlatformUtils::InitializeWinLibrary())
	{
		CLOG_DEBUG("Windows library start working on Windows (default true for linux)");
	}
	else
	{
		CLOG_DEBUG("Cannnot initialize windows library!");
		return result;
	}
	InitAcceptor();
	InitSocketWrapper();
	InitServiceHandler(json_data);

	if (m_p_server_acceptor->Initialize(m_ip_address, m_port, connections))
	{
		CLOG_DEBUG("CAcceptor was successfully initialized");
		m_is_host_initialized = result = true;
		return result;
	}
	CLOG_ERROR("Fail CAcceptor initialization");
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

bool CServiceHost::Execute()
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	if(!m_is_host_initialized)
	{
		CLOG_DEBUG_WITH_PARAMS("CServiceHost is not initialized", m_is_host_initialized);
		return result;
	}
	
	CLOG_PROD(std::string(10u, '*') + " START SERVER " + std::string(10u, '*'));

	result = HandleEvents();
	CLOG_PROD(std::string(10u, '*') + " STOP SERVER " + std::string(10u, '*'));
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

void CServiceHost::ShutDown()
{
	CLOG_DEBUG_START_FUNCTION();
	DeleteAllClients();
	m_p_server_acceptor.reset();
	CLOG_DEBUG_END_FUNCTION();
}

void CServiceHost::InitAcceptor()
{
	CLOG_DEBUG_START_FUNCTION();
	m_p_server_acceptor = std::make_unique<CAcceptor>(m_is_socket_blocked,
		m_socket_timeout, m_event);
	CLOG_TRACE_VAR_CREATION(m_p_server_acceptor);
	CLOG_DEBUG_END_FUNCTION();
}

void CServiceHost::InitServiceHandler(
	CRequestHandler& request_handler)
{
	CLOG_DEBUG_START_FUNCTION();
	m_p_service_handler =
		std::make_unique<CServiceConnectionHandler>(std::move(request_handler));
	CLOG_TRACE_VAR_CREATION(m_p_service_handler);
	CLOG_DEBUG_END_FUNCTION();
}

void CServiceHost::InitSocketWrapper()
{
	CLOG_DEBUG_START_FUNCTION();
	m_p_stream = std::make_unique<CSocketWrapper>();
	CLOG_TRACE_VAR_CREATION(m_p_stream);
	CLOG_DEBUG_END_FUNCTION();
}

bool CServiceHost::HandleEvents()
{
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG("Start accepting clients");
	AcceptClients();
	CLOG_DEBUG("Start handling clients");
	while (!m_event.WaitFor(std::chrono::milliseconds(1)))
	{
		if (!m_clients_statuses.empty())
		{
			AcceptRequest();
		}
	}
	CLOG_DEBUG_END_FUNCTION();
	return true;
}

void CServiceHost::AcceptRequest()
{
	
	int max_sd = 0;
	fd_set read_fds;
	fd_set write_fds;
	fd_set error_fds;
	timeval time_out;
	time_out.tv_sec = 0;
	
	FD_ZERO(&read_fds);
	FD_ZERO(&write_fds);
	FD_ZERO(&error_fds);
	
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		
		for (auto client : m_clients_statuses)
		{
			if (client.second)
			{
				continue;
			}
			FD_SET(client.first.GetSocketFD(), &read_fds);
			FD_SET(client.first.GetSocketFD(), &write_fds);
			FD_SET(client.first.GetSocketFD(), &error_fds);
			if (client.first.GetSocketFD() > max_sd)
			{
				max_sd = client.first.GetSocketFD();
			}
		}
		int select_result = select(max_sd + 1, &read_fds, &write_fds, 
			&error_fds, &time_out);

		if(select_result <= 0)
		{
			CLOG_DEBUG_WITH_PARAMS("Error select function", select_result);
		}

		for (auto it = m_clients_statuses.begin(); 
			it != m_clients_statuses.end(); ++it)
		{
			if (it->second)
			{
				continue;
			}
			if (FD_ISSET(it->first.GetSocketFD(), &error_fds))
			{
				CLOG_DEBUG_WITH_PARAMS("FD_ISSET found broken socket",
					it->first.GetSocketFD());
				DeleteBrokenSocket(it->first.GetSocketFD());
				return;
			}
			if (FD_ISSET(it->first.GetSocketFD(), &read_fds))
			{
				CLOG_DEBUG_WITH_PARAMS("FD_ISSET accepted new request from the socket",
					it->first.GetSocketFD(), it->second);
				it->second = true;
				AddClientToThread(it->first);
			}
		}
	}
}

void CServiceHost::AddClientToThread(const CSocket& client)
{
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_WITH_PARAMS("Add client to the thread", client.GetSocketFD());
	m_p_pool->Enqueue([this, &client]()
		{
			CLOG_DEBUG_WITH_PARAMS("New client was added to the thread with socket ",
				client.GetSocketFD());
			if (m_p_service_handler->HandleEvent(client,
				EEventType::REQUEST_DATA))
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				for (auto it = m_clients_statuses.begin(); 
					it != m_clients_statuses.end(); ++it)

				{
					if (it->first.GetSocketFD() == client.GetSocketFD())
					{
						it->second = false;
						CLOG_DEBUG_WITH_PARAMS("Stop working with the client", 
							client.GetSocketFD());
					}
				}
			}
			else
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				DeleteBrokenSocket(client.GetSocketFD());
			}
			});
	CLOG_DEBUG_END_FUNCTION();
}

bool CServiceHost::DeleteBrokenSocket(const int socket_descriptor)
{
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_WITH_PARAMS("We should delete client", socket_descriptor);
	for(auto it = m_clients_statuses.begin(); 
		it != m_clients_statuses.end(); ++it)
	{
		if(it->first.GetSocketFD() == socket_descriptor)
		{
			PlatformUtils::CloseSocket(it->first.GetSocketFD());
			CLOG_DEBUG_WITH_PARAMS("Erase client", it->first.GetSocketFD());
			m_clients_statuses.erase(it);
			CLOG_DEBUG_WITH_PARAMS("Now we have clients", 
				m_clients_statuses.size());
			return true;
		}
	}
	CLOG_DEBUG_END_FUNCTION();
	return false;
}

void CServiceHost::AcceptClients()
{
	CLOG_DEBUG_START_FUNCTION();
	
	m_p_pool->Enqueue([this]()
		{
			while (!m_event.WaitFor(std::chrono::milliseconds(1)))
			{
				CSocket accepted_client(GlobalVariable::c_invalid_socket);
				if(m_p_server_acceptor->AcceptNewClient(accepted_client)
				&& accepted_client.IsValidSocket())
				{
					std::lock_guard<std::mutex> lock(m_mutex);

					CLOG_DEBUG_WITH_PARAMS("Was accepted new client with descriptor",
						accepted_client.GetSocketFD());
					m_clients_statuses.push_back(std::pair(accepted_client, 
						false));
					CLOG_DEBUG_WITH_PARAMS("We have clients after adding", 
						m_clients_statuses.size());
				}
			}
		});
	CLOG_DEBUG_END_FUNCTION();
}

void CServiceHost::DeleteAllClients()
{
	CLOG_DEBUG_START_FUNCTION();
	while(!m_clients_statuses.empty())
	{
		DeleteBrokenSocket(m_clients_statuses.front().first.GetSocketFD());
	}
	CLOG_DEBUG_WITH_PARAMS("We have clients", m_clients_statuses.size());
	CLOG_DEBUG_END_FUNCTION();
}
