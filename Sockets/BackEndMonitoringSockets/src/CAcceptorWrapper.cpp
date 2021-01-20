#include "stdafx.h"
#include "CAcceptorWrapper.h"
#include "DataReceiver.h"
#include "CServiceConnectionHandler.h"
#include "CEvent.h"

CAcceptorWrapper::CAcceptorWrapper(int port, const std::string& ip_address, 
	size_t num_threads, CEvent& event)
	: m_event(event)
{
	m_server_acceptor = InitAcceptor(1111, "127.0.0.1");
	m_stream = InitSocketWrapper();
	m_service_handler = InitServiceHandler();
	m_pool = InitThreadPool(num_threads, m_event);
}

void CAcceptorWrapper::StartServer()
{
	std::cout << "Start server" << std::endl;
	int handle = SOCKET_ERROR;
	while (!m_event.WaitFor(std::chrono::nanoseconds(1)))
	{
		if ((handle = m_server_acceptor->GetConnectedHandle()) != SOCKET_ERROR)
		{
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

std::unique_ptr<CThreadPool> CAcceptorWrapper::InitThreadPool(size_t num_threads, 
	CEvent& event)
{
	return std::move(std::make_unique<CThreadPool>(num_threads, event));
}

std::unique_ptr<CAcceptor> CAcceptorWrapper::InitAcceptor(int port, 
	const std::string& address)
{
	return std::move(std::make_unique<CAcceptor>(port, address));
}

std::unique_ptr<CServiceHandler> CAcceptorWrapper::InitServiceHandler()
{
	return std::move(std::make_unique<CServiceConnectionHandler>());
}

std::unique_ptr<CSocketWrapper> CAcceptorWrapper::InitSocketWrapper()
{
	return std::move(std::make_unique<CSocketWrapper>());
}

