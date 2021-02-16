#include "stdafx.h"

#include "CServiceConnectionHandler.h"
#include "CThreadPool.h"
#include "CServiceHost.h"
#include "CAcceptor.h"
#include "CSocketWrapper.h"
#include "Log.h"

CServiceHost::CServiceHost(int port, const std::string& ip_address,
    bool is_blocked, int socket_timeout, CEvent& event) :
	m_port(port), m_ip_address(ip_address), m_event(event),
	m_is_socket_blocked(is_blocked), m_socket_timeout(socket_timeout),
	m_num_working_threads(0), m_is_host_initialized(false)
{ }

CServiceHost::~CServiceHost()
{
	PlatformUtils::FinalizeWinLibrary();
}

bool CServiceHost::Initialize(std::shared_ptr<CThreadPool> pool,
	CDataReceiver& json_data, const int connections)
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
		CDataReceiver& json_data)
{
	CLOG_DEBUG_START_FUNCTION();
	m_p_service_handler =
		std::make_unique<CServiceConnectionHandler>(std::move(json_data));
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
	while (!m_event.WaitFor(std::chrono::milliseconds(100)))
	{
		if (m_num_working_threads == 0 && !m_clients.empty() && AcceptRequest())
		{
			CLOG_DEBUG("Clients was handled");
		}
	}
	CLOG_DEBUG_END_FUNCTION();
	return true;
}

bool CServiceHost::AcceptRequest()
{
	int max_sd = 0;
	fd_set read_fds;
	fd_set write_fds;
	fd_set error_fds;
	timeval time_out;
	time_out.tv_sec = 0;
	int select_result = 0;
	
	size_t num_clients = 0u;
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		num_clients = m_clients.size();
	}
	
	FD_ZERO(&read_fds);
	FD_ZERO(&write_fds);
	FD_ZERO(&error_fds);
	
	int current_socket = 0;
	for (size_t i = 0; i < num_clients; ++i)
	{
		current_socket = m_clients[i].GetSocketFD();
		FD_SET(current_socket, &read_fds);
		FD_SET(current_socket, &write_fds);
		FD_SET(current_socket, &error_fds);
		if (current_socket > max_sd)
		{
			max_sd = current_socket;
		}
	}
	
	select_result = select(max_sd + 1, &read_fds, &write_fds, 
		&error_fds, &time_out);

	if(select_result <= 0)
	{
		CLOG_DEBUG_WITH_PARAMS("Error select function", select_result);
		//return false;
	}

	for (size_t i = 0; i < num_clients; ++i)
	{
		if (FD_ISSET(m_clients[i].GetSocketFD(), &error_fds))
		{
			CLOG_DEBUG_WITH_PARAMS("FD_ISSET found broken socket",
				m_clients[i].GetSocketFD());
			m_disconnected_clients.push_back(m_clients[i].GetSocketFD());
			continue;
		}
		if (FD_ISSET(m_clients[i].GetSocketFD(), &read_fds))
		{
			CLOG_DEBUG_WITH_PARAMS("FD_ISSET accepted new request from the socket",
				m_clients[i].GetSocketFD());
			AddClientToThread(m_clients[i]);
		}
	}
	
	if(!m_disconnected_clients.empty())
	{
		DeleteDisconnectedClients();
		m_disconnected_clients.clear();
	}
	return true;
}

void CServiceHost::AddClientToThread(const CSocket& client)
{
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_WITH_PARAMS("Add client to the thread", client.GetSocketFD());
	m_p_pool->Enqueue([this, &client]()
		{
			++m_num_working_threads;
			CLOG_DEBUG_WITH_PARAMS("New client was added to the thread with socket ",
				client.GetSocketFD());
			if (!m_p_service_handler->HandleEvent(client,
				EEventType::REQUEST_DATA))
			{
				CLOG_DEBUG_WITH_PARAMS("Add socket to list for deleting", client.GetSocketFD());
				m_disconnected_clients.push_back(client.GetSocketFD());
			}
			--m_num_working_threads;
		});
	CLOG_DEBUG_WITH_PARAMS("We have threads", m_num_working_threads);
	CLOG_DEBUG_END_FUNCTION();
}

bool CServiceHost::DeleteBrokenSocket(const int socket_descriptor)
{
	CLOG_DEBUG_START_FUNCTION();
	std::lock_guard<std::mutex> lock(m_mutex);
	
	CLOG_DEBUG_WITH_PARAMS("We should delete client", socket_descriptor);
	for(auto it = m_clients.begin(); it != m_clients.end(); ++it)
	{
		if(it->GetSocketFD() == socket_descriptor)
		{
			PlatformUtils::CloseSocket(it->GetSocketFD());
			CLOG_DEBUG_WITH_PARAMS("Erase client", it->GetSocketFD());
			m_clients.erase(it);
			CLOG_DEBUG_WITH_PARAMS("Now we have clients", m_clients.size());
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
			while (!m_event.WaitFor(std::chrono::milliseconds(100)))
			{
				CSocket accepted_client(c_invalid_socket);
				if(m_p_server_acceptor->AcceptNewClient(accepted_client)
				&& accepted_client.IsValidSocket())
				{
					std::lock_guard<std::mutex> lock(m_mutex);
					CLOG_DEBUG_WITH_PARAMS("Was accepted new client with descriptor",
						accepted_client.GetSocketFD());
					m_clients.push_back(accepted_client);
					CLOG_DEBUG_WITH_PARAMS("We have clients after adding", 
						m_clients.size());
				}
			}
		});
	CLOG_DEBUG_END_FUNCTION();
}

void CServiceHost::DeleteAllClients()
{
	CLOG_DEBUG_START_FUNCTION();
	while(!m_clients.empty())
	{
		DeleteBrokenSocket(m_clients.front().GetSocketFD());
	}
	CLOG_DEBUG_WITH_PARAMS("We have clients", m_clients.size());
	CLOG_DEBUG_END_FUNCTION();
}

void CServiceHost::DeleteDisconnectedClients()
{
	CLOG_DEBUG_START_FUNCTION();

	CLOG_DEBUG_WITH_PARAMS("We should delete disconnected clients", 
		m_disconnected_clients.size());
	for (size_t i = 0; i < m_disconnected_clients.size(); ++i)
	{
		DeleteBrokenSocket(m_disconnected_clients[i]);
	}
	CLOG_DEBUG_END_FUNCTION();
}
