#include "stdafx.h"

#include "CServiceConnectionHandler.h"
#include "CEvent.h"
#include "PlatformUtils.h"
#include "CLogger/include/Log.h"
#include "CThreadPool.h"
#include "CAcceptorWrapper.h"

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
	while (!m_event.WaitFor(std::chrono::nanoseconds(1000)))
	{
		if (m_p_server_acceptor->Accept(socket_fd))
		{
			CLOG_DEBUG_WITH_PARAMS("New client with socket desciptor ",
				socket_fd, " was accepted");
			AddClientToThread(socket_fd);
		}
		else
		{
			if (m_p_server_acceptor->IsTimeOutWithoutConnections())
			{
				CLOG_TRACE("Connection timeout for the client");
			}
		}
	}
	CLOG_DEBUG_END_FUNCTION();
	return true;
}

void CAcceptorWrapper::AddClientToThread(int socket_fd)
{
	m_p_pool->Enqueue([this, socket_fd]()
		{
			CLOG_DEBUG("New client was added to the thread");
			while (
				m_p_service_handler->HandleEvent(socket_fd,
					EEventType::REQUEST_DATA) &&
				!m_event.WaitFor(std::chrono::nanoseconds(1000)));
		});
}
