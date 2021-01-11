#include "stdafx.h"

CAcceptorWrapper::CAcceptorWrapper()
{
	m_dispatcher = CInitiationDispatcher::GetInstance();
	m_server_acceptor = new CAcceptor(27015, "127.0.0.1",
		m_dispatcher);
	std::cout << m_dispatcher << " CInitiationDispatcher address"
		<< std::endl;

}

void CAcceptorWrapper::Start()
{
	while (true)
	{
		if (m_server_acceptor->Listening())
		{
			m_dispatcher->HandleEvents();
		}
	}
}

