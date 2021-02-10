#include "stdafx.h"

#include "CServiceConnectionHandler.h"
#include "CEvent.h"
#include "PlatformUtils.h"
#include "CLogger/include/Log.h"
#include "CThreadPool.h"
#include "CAcceptorWrapper.h"
#include <map>


CAcceptorWrapper::CAcceptorWrapper(int port, const std::string& ip_address,
                                   bool is_blocked, int socket_timeout, CEvent& event) :
	m_port(port), m_ip_address(ip_address), m_event(event),
	m_is_socket_blocked(is_blocked), m_socket_timeout(socket_timeout)
{ }

CAcceptorWrapper::~CAcceptorWrapper()
{
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_END_FUNCTION();
	PlatformUtils::FinalizeWinLibrary();
}

bool CAcceptorWrapper::Initialize(std::shared_ptr<CThreadPool> pool,
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
	InitAcceptor(m_port, m_ip_address);
	InitSocketWrapper();
	InitServiceHandler(json_data);

	if (!m_p_server_acceptor->Initialize(m_ip_address, m_port, connections))
	{
		return false;
	}

	CLOG_DEBUG_END_FUNCTION();

	return true;
}

bool CAcceptorWrapper::Execute()
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	CLOG_PROD(std::string(10u, '*') + " START SERVER " + std::string(10u, '*'));

	result = HandleEvents();
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

bool CAcceptorWrapper::StopSocket()
{
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG("Server socket was closed");
	CLOG_PROD(std::string(10u, '*') + " STOP SERVER " + std::string(10u, '*'));
	CLOG_DEBUG_END_FUNCTION();
	return m_p_server_acceptor->CloseSocket();
}

void CAcceptorWrapper::InitAcceptor(int port,
	const std::string& address)
{
	CLOG_DEBUG_START_FUNCTION();
	m_p_server_acceptor = std::make_unique<CAcceptor>(m_is_socket_blocked,
		m_socket_timeout, m_event);
	CLOG_TRACE_VAR_CREATION(m_p_server_acceptor);
	CLOG_DEBUG_END_FUNCTION();
}

void CAcceptorWrapper::InitServiceHandler(
		CDataReceiver& json_data)
{
	CLOG_DEBUG_START_FUNCTION();
	m_p_service_handler =
		std::make_unique<CServiceConnectionHandler>(std::move(json_data));
	CLOG_TRACE_VAR_CREATION(m_p_service_handler);
	CLOG_DEBUG_END_FUNCTION();
}

void CAcceptorWrapper::InitSocketWrapper()
{
	CLOG_DEBUG_START_FUNCTION();
	m_p_stream = std::make_unique<CSocketWrapper>();
	CLOG_TRACE_VAR_CREATION(m_p_stream);
	CLOG_DEBUG_END_FUNCTION();
}

bool CAcceptorWrapper::HandleEvents()
{
	CLOG_DEBUG_START_FUNCTION();
	int socket_fd = c_error_socket;
	bool is_broken_socket = false;

	while (!m_event.WaitFor(std::chrono::milliseconds(100)))
	{
		if(m_p_server_acceptor->AcceptNewClient(socket_fd))
		{
			m_clients_statuses.insert(std::pair<int, bool>(socket_fd, false));
			socket_fd = c_error_socket;
		}

		if (AcceptRequest())
		{
			CheckBrokenSockets();
		}
	}
	CLOG_DEBUG_END_FUNCTION();
	return true;
}

bool CAcceptorWrapper::AcceptRequest()
{
	int max_sd = 0;
	fd_set read_fds;
	fd_set error_fds;
	
	FD_ZERO(&read_fds);
	FD_ZERO(&error_fds);

	for (auto sock : m_clients_statuses)
	{
		FD_SET(sock.first, &read_fds);
		FD_SET(sock.first, &error_fds);
		if (sock.first > max_sd)
		{
			max_sd = sock.first;
		}
	}

	select(max_sd + 1, &read_fds, 0, &error_fds, 0);

	auto it = m_clients_statuses.begin();
	while (it != m_clients_statuses.end())
	{
		if (FD_ISSET(it->first, &error_fds))
		{
			it->second = true;
			CLOG_DEBUG_WITH_PARAMS("FD_ISSET found broken socket", it->first);
			continue;
		}
		else if (FD_ISSET(it->first, &read_fds))
		{
			CLOG_DEBUG_WITH_PARAMS("FD_ISSET accepted new request from the socket",
				it->first);
			AddClientToThread(it->first, it->second);
		}

		++it;
	}

	return true;
}

void CAcceptorWrapper::AddClientToThread(int socket_fd, bool& is_broken_socket)
{
	m_p_pool->Enqueue([this, socket_fd, &is_broken_socket]()
		{
			CLOG_DEBUG_WITH_PARAMS("New client was added to the thread with socket ",
				socket_fd);
			if (!m_p_service_handler->HandleEvent(socket_fd,
				EEventType::REQUEST_DATA))
			{
				is_broken_socket = true;
			}
			CLOG_DEBUG_WITH_PARAMS("Exit thread for the client with socket ",
				socket_fd);
		});
}

void CAcceptorWrapper::CheckBrokenSockets()
{
	auto it = m_clients_statuses.begin();
	while (it != m_clients_statuses.end())
	{
		if (it->second == true)		// if socket is broken
		{
			CLOG_DEBUG_WITH_PARAMS("Erase client", it->first, m_clients_statuses.size());
			m_clients_statuses.erase(it);
			it = m_clients_statuses.begin();
			CLOG_DEBUG_WITH_PARAMS("Now we have clients", m_clients_statuses.size());
			continue;
		}

		++it;
	}
}