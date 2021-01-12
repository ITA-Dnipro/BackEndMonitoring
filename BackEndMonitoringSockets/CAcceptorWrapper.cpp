#include "stdafx.h"
#include "CAcceptorWrapper.h"

CAcceptorWrapper::CAcceptorWrapper(size_t num_threads, CEvent& event)
	: m_event(event)
{

	m_server_acceptor = std::make_unique<CAcceptor>(1111, "127.0.0.1");
	m_stream = std::make_unique<CSocketWrapper>(m_server_acceptor->GetHandle());
	m_service_handler = std::make_unique<CServiceConnectionHandler>
		(m_server_acceptor->GetHandle());
	m_pool = std::make_unique<CThreadPool>(num_threads, m_event);
}

void CAcceptorWrapper::Start()
{
	std::cout << "Start server" << std::endl;
	int handle = SOCKET_ERROR;
	while (true)
	{
		if ((handle = m_server_acceptor->GetConnectedHandle()) != SOCKET_ERROR)
		{

			m_pool->Enqueue([this, &handle]() {
				m_service_handler->HandleEvent(handle, 
					EventType::REQUEST_DATA);
				});
			//m_service_handler->HandleEvent(handle, EventType::REQUEST_DATA);

		}
	}
}

