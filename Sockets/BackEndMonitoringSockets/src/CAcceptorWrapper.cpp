#include "stdafx.h"
#include "CAcceptorWrapper.h"
#include "DataReceiver.h"
#include "CServiceConnectionHandler.h"
#include "CEvent.h"
#include "PlatformUtils.h"
CAcceptorWrapper::CAcceptorWrapper(int port, const std::string& ip_address, 
	CEvent& event, std::shared_ptr<CThreadPool> pool, bool is_blocked, 
	int socket_timeout)	: m_event(event), m_is_socket_blocked(is_blocked), 
	m_socket_timeout(socket_timeout), m_pool(pool)
{
	Initialize(port, ip_address);
}

CAcceptorWrapper::~CAcceptorWrapper()
{
	PlatformUtils::FinalizeWinLibrary();
}

void CAcceptorWrapper::StartServer()
{
	std::cout << "Start server" << std::endl;
	if (m_is_socket_blocked)
	{
		//CLOG_DEBUG("Start handling events with blocked server socket");
		HandleBlockingEvents();
	}
	else
	{
		//CLOG_DEBUG("Start handling events with unblocked server socket");
		HandleNonBlockingEvents();
	}
}

bool CAcceptorWrapper::StopSocket()
{
	return m_server_acceptor->CloseSocket();
}

void CAcceptorWrapper::Initialize(int port, const std::string& ip_address)
{
	PlatformUtils::InitializeWinLibrary();
	m_server_acceptor = InitAcceptor(port, ip_address);
	m_stream = InitSocketWrapper();
	m_service_handler = InitServiceHandler();
}


std::unique_ptr<CAcceptor> CAcceptorWrapper::InitAcceptor(int port, 
	const std::string& address)
{
	return std::move(std::make_unique<CAcceptor>(port, address, 
		m_is_socket_blocked));
}

std::unique_ptr<CServiceHandler> CAcceptorWrapper::InitServiceHandler()
{
	return std::move(std::make_unique<CServiceConnectionHandler>());
}

std::unique_ptr<CSocketWrapper> CAcceptorWrapper::InitSocketWrapper()
{
	return std::move(std::make_unique<CSocketWrapper>());
}

void CAcceptorWrapper::HandleNonBlockingEvents()
{
	int max_sd;
	FD_SET read_fds;
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
}

void CAcceptorWrapper::HandleBlockingEvents()
{
	int socket_fd = ERROR_SOCKET;
	while (!m_event.WaitFor(std::chrono::nanoseconds(1)))
	{
		AddClientToThread(socket_fd);
	}
}

void CAcceptorWrapper::AddClientToThread(int& socket_fd)
{
	if ((socket_fd = m_server_acceptor->GetConnectedFD()) > 0)
	{
		//CLOG_DEBUG_WITH_PARAMS("Accept a new client with a socket ", socket_fd);
		m_pool->Enqueue([this, &socket_fd]()
			{
				while (!m_event.WaitFor(std::chrono::nanoseconds(1000)))
				{
					m_service_handler->HandleEvent(socket_fd,
						EventType::REQUEST_DATA);
				}
			});
	}
}