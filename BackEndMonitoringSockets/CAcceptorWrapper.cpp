#include "CAcceptorWrapper.h"

namespace AcceptorWrapper
{
	CAcceptorWrapper::CAcceptorWrapper()
	{
		m_dispatcher = CDispatcher::GetInstance();
		m_server_acceptor = new Acceptor::CAcceptor(27015, "127.0.0.1", 
			m_dispatcher);
		std::cout << m_dispatcher << std::endl;

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
}

