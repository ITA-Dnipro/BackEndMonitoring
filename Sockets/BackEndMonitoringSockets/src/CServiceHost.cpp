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
	m_is_socket_blocked(is_blocked), m_socket_timeout(socket_timeout)
{ }

CServiceHost::~CServiceHost()
{
	PlatformUtils::FinalizeWinLibrary();
}

bool CServiceHost::Initialize(std::shared_ptr<CThreadPool> pool,
	CDataReceiver& json_data, const int connections)
{
	CLOG_DEBUG_START_FUNCTION();
	m_p_pool = pool;
	if (PlatformUtils::InitializeWinLibrary())
	{
		CLOG_DEBUG("Windows library start working on Windows (default true for linux)");
	}
	else
	{
		CLOG_DEBUG("Cannnot initialize windows library!");
		return false;
	}
	InitAcceptor();
	InitSocketWrapper();
	InitServiceHandler(json_data);

	if (!m_p_server_acceptor->Initialize(m_ip_address, m_port, connections))
	{
		CLOG_ERROR("Fail CAcceptor initialization");
		return false;
	}
	CLOG_DEBUG("CAcceptor was successfully initialized");
	CLOG_DEBUG_END_FUNCTION();

	return true;
}

bool CServiceHost::Execute()
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	CLOG_PROD(std::string(10u, '*') + " START SERVER " + std::string(10u, '*'));

	result = HandleEvents();
	CLOG_PROD(std::string(10u, '*') + " STOP SERVER " + std::string(10u, '*'));
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

void CServiceHost::ShutDown()
{
	CLOG_DEBUG_START_FUNCTION();
	DeleteClients();
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
	while (!m_event.WaitFor(std::chrono::milliseconds(200)))
	{
		if (!m_clients.empty() && AcceptRequest())
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
	
	FD_ZERO(&read_fds);
	FD_ZERO(&write_fds);
	FD_ZERO(&error_fds);
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		for (auto it = m_clients.begin(); it != m_clients.end(); ++it)
		{
			FD_SET(it->GetSocketFD(), &read_fds);
			FD_SET(it->GetSocketFD(), &write_fds);
			FD_SET(it->GetSocketFD(), &error_fds);
			if (it->GetSocketFD() > max_sd)
			{
				max_sd = it->GetSocketFD();
			}
		}
	}
	
	select_result = select(max_sd + 1, &read_fds, &write_fds, 
		&error_fds, &time_out);

	if(select_result <= 0)
	{
		return false;
	}

	{
		std::lock_guard<std::mutex> lock(m_mutex);

		auto it = m_clients.begin();
		while (it != m_clients.end())
		{
			if (FD_ISSET(it->GetSocketFD(), &error_fds))
			{
				CLOG_DEBUG_WITH_PARAMS("FD_ISSET found broken socket",
					it->GetSocketFD());
				DeleteBrokenSocket(it->GetSocketFD());
				return false;
			}
			if (FD_ISSET(it->GetSocketFD(), &read_fds))
			{
				CLOG_DEBUG_WITH_PARAMS("FD_ISSET accepted new request from the socket",
					it->GetSocketFD());
				AddClientToThread(*it);
			}

			++it;
		}
	}
	
	return true;
}

void CServiceHost::AddClientToThread(const CSocket& client)
{
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_WITH_PARAMS("Add client to the thread", client.GetSocketFD());
	m_p_pool->Enqueue([this, &client]()
		{
			CLOG_DEBUG_WITH_PARAMS("New client was added to the thread with socket ",
				client.GetSocketFD());
			if (!m_p_service_handler->HandleEvent(client,
				EEventType::REQUEST_DATA))
			{
				DeleteBrokenSocket(client.GetSocketFD());
				CLOG_DEBUG_WITH_PARAMS("Close socket", client.GetSocketFD());
			}
			CLOG_DEBUG_WITH_PARAMS("Exit thread for the client with socket ",
				client.GetSocketFD());
		});
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
	std::lock_guard<std::mutex> lock(m_mutex);
	
	m_p_pool->Enqueue([this]()
		{
			while (!m_event.WaitFor(std::chrono::milliseconds(100)))
			{
				CSocket accepted_client(m_port, m_ip_address, c_invalid_socket);
				if(m_p_server_acceptor->AcceptNewClient(accepted_client)
				&& accepted_client.IsValidSocket())
				{
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

void CServiceHost::DeleteClients()
{
	CLOG_DEBUG_START_FUNCTION();
	while(!m_clients.empty())
	{
		DeleteBrokenSocket(m_clients.front().GetSocketFD());
	}
	CLOG_DEBUG_WITH_PARAMS("We have clients", m_clients.size());
	CLOG_DEBUG_END_FUNCTION();
}
