#include "stdafx.h"
#include "CAcceptorWrapper.h"

CAcceptorWrapper::CAcceptorWrapper(int port, const std::string& ip_address, 
	CEvent& event, std::shared_ptr<CThreadPool> pool, 
	std::shared_ptr<CLogger> logger)
	: m_event(event), m_pool(pool), m_logger(logger)
{
	m_server_acceptor = InitAcceptor(1111, "127.0.0.1");
	m_stream = InitSocketWrapper(m_server_acceptor->GetHandle());
	m_service_handler = InitServiceHandler(m_server_acceptor->GetHandle());
}

void CAcceptorWrapper::StartServer()
{
	std::cout << "Start server" << std::endl;
	int handle = SOCKET_ERROR;
	while (!m_event.WaitFor(std::chrono::nanoseconds(1)))
	{
		if ((handle = m_server_acceptor->GetConnectedHandle()) != SOCKET_ERROR)
		{
			CLOG_DEBUG_WITH_PARAMS(*m_logger, "Connected with a new socket ", 
				handle);
			m_pool->Enqueue([this, &handle]()
			{
				while (!m_event.WaitFor(std::chrono::nanoseconds(1)))
				{
					m_service_handler->HandleEvent(handle,
						EventType::REQUEST_DATA);
				}
			});
		}
	}
}

bool CAcceptorWrapper::StopSocket()
{
	return m_server_acceptor->CloseSocket();
}

std::unique_ptr<CAcceptor> CAcceptorWrapper::InitAcceptor(int port, 
	const std::string& address)
{
	return std::move(std::make_unique<CAcceptor>(port, address,
		m_logger));
}

std::unique_ptr<CServiceConnectionHandler> CAcceptorWrapper::InitServiceHandler
	(int handle)
{
	return std::move(std::make_unique<CServiceConnectionHandler>(handle, 
		m_logger));
}

std::unique_ptr<CSocketWrapper> CAcceptorWrapper::InitSocketWrapper(int handle)
{
	return std::move(std::make_unique<CSocketWrapper>(handle, m_logger));
}

