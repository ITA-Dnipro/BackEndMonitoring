#include "stdafx.h"
#include "CAcceptorWrapper.h"

CAcceptorWrapper::CAcceptorWrapper()
{
	m_dispatcher = CInitiationDispatcher::GetInstance();
	m_server_acceptor = new CAcceptor(1111, "127.0.0.1", m_dispatcher);
	std::cout << m_dispatcher << " CInitiationDispatcher address"
		<< std::endl;

}

CAcceptorWrapper::~CAcceptorWrapper()
{
	delete m_server_acceptor;
	delete m_dispatcher;
}

void CAcceptorWrapper::Start()
{
	int handle = SOCKET_ERROR;
	while (true)
	{
		if ((handle = m_server_acceptor->GetConnectedHandle()) != SOCKET_ERROR)
		{
			std::cout << "CAcceptorWrapper Start" << handle << std::endl;
			m_dispatcher->HandleEvents();
		}
	}
	std::cout << "Exit start" << std::endl;
}

