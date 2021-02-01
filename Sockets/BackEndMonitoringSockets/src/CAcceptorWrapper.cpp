#include "Sockets/BackEndMonitoringSockets/include/stdafx.h"

#include "CAcceptorWrapper.h"
#include "CServiceConnectionHandler.h"
#include "CEvent.h"
#include "PlatformUtils.h"
#include "Log.h"

CAcceptorWrapper::CAcceptorWrapper(int port, const std::string& ip_address,
	CEvent& event, std::shared_ptr<CThreadPool> pool,
	bool is_blocked, int socket_timeout, CDataReceiver json_data) :
	m_event(event), m_is_socket_blocked(is_blocked),
	m_socket_timeout(socket_timeout), m_pool(pool)
{
	Initialize(port, ip_address, json_data);
}

CAcceptorWrapper::~CAcceptorWrapper()
{
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_END_FUNCTION();
	PlatformUtils::FinalizeWinLibrary();
}

void CAcceptorWrapper::StartServer()
{
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG(std::string(10u, '*') + " START SERVER " + std::string(10u, '*'));

	if (m_is_socket_blocked)
	{
		CLOG_DEBUG("Starting handling blocking events");
		HandleBlockingEvents();
	}
	else
	{
		CLOG_DEBUG("Starting handling non blocking events");
		HandleNonBlockingEvents();
	}
	CLOG_DEBUG_END_FUNCTION();
}

bool CAcceptorWrapper::StopSocket()
{
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG("Server socket was closed");
	CLOG_DEBUG_END_FUNCTION();
	return m_server_acceptor->CloseSocket();
}

void CAcceptorWrapper::Initialize(int port, const std::string& ip_address,
	CDataReceiver& json_data)
{
	CLOG_DEBUG_START_FUNCTION();
	if(PlatformUtils::InitializeWinLibrary())
	{
		CLOG_DEBUG("Windows library start working on Windows (default true for linux)");
	}
	else
	{
		CLOG_DEBUG("Cannnot initialize windows library!");
	}
	InitAcceptor(port, ip_address);
	InitSocketWrapper();
	InitServiceHandler(json_data);
	CLOG_DEBUG_END_FUNCTION();
}


void CAcceptorWrapper::InitAcceptor(int port, 
	const std::string& address)
{
	CLOG_DEBUG_START_FUNCTION();
	m_server_acceptor = std::make_unique<CAcceptor>(port, address,
		m_is_socket_blocked);
	CLOG_TRACE_VAR_CREATION(m_server_acceptor);
	CLOG_DEBUG_END_FUNCTION();
}

void CAcceptorWrapper::InitServiceHandler(
		CDataReceiver& json_data)
{
	CLOG_DEBUG_START_FUNCTION();
	m_service_handler = std::make_unique<CServiceConnectionHandler>(std::move(json_data));
	CLOG_TRACE_VAR_CREATION(m_service_handler);
	CLOG_DEBUG_END_FUNCTION();
}

void CAcceptorWrapper::InitSocketWrapper()
{
	CLOG_DEBUG_START_FUNCTION();
	m_stream = std::make_unique<CSocketWrapper>();
	CLOG_TRACE_VAR_CREATION(m_stream);
	CLOG_DEBUG_END_FUNCTION();
}

void CAcceptorWrapper::HandleNonBlockingEvents()
{
	CLOG_DEBUG_START_FUNCTION();
	int max_sd;
	fd_set read_fds;
	int socket_fd = ERROR_SOCKET;
	timeval time_out;
	time_out.tv_sec = m_socket_timeout;

	while (!m_event.WaitFor(std::chrono::nanoseconds(1000)))
	{
		FD_ZERO(&read_fds);

		FD_SET(m_server_acceptor->GetHandle(), &read_fds);
		max_sd = m_server_acceptor->GetHandle();

		select(max_sd + 1, &read_fds, NULL, NULL, &time_out);

		if (FD_ISSET(m_server_acceptor->GetHandle(), &read_fds))
		{
			AddClientToThread(socket_fd);
		}
	}
	CLOG_DEBUG_END_FUNCTION();
}

void CAcceptorWrapper::HandleBlockingEvents()
{
	CLOG_DEBUG_START_FUNCTION();
	int socket_fd = ERROR_SOCKET;
	while (!m_event.WaitFor(std::chrono::nanoseconds(1000)))
	{
		AddClientToThread(socket_fd);
	}
	CLOG_DEBUG_END_FUNCTION();
}

void CAcceptorWrapper::AddClientToThread(int& socket_fd)
{
	CLOG_DEBUG_START_FUNCTION();
	if ((socket_fd = m_server_acceptor->GetConnectedFD()) > 0)
	{
		CLOG_DEBUG_WITH_PARAMS("New client with socket desciptor ", socket_fd, 
			" was accepted");
		m_pool->Enqueue([this, socket_fd]()
			{
				while (
					m_service_handler->HandleEvent(socket_fd,
						EventType::REQUEST_DATA) && 
						!m_event.WaitFor(std::chrono::nanoseconds(1000)))
				{ }
			});
	}
	CLOG_DEBUG_END_FUNCTION();
}
