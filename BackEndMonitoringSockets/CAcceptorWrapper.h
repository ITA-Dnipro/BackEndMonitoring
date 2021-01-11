#pragma once
#include "CAcceptor.h"
#include "CInitiationDispatcher.h"

using CDispatcher = Dispatcher::CInitiationDispatcher;

namespace AcceptorWrapper
{
	class CAcceptorWrapper
	{
	public:
		CAcceptorWrapper();
		void Start();
		//void SendMessage(const std::string& message);
		//void ReceiveMessage();

	private:
		Acceptor::CAcceptor* m_server_acceptor;
		CDispatcher* m_dispatcher;

	};
}

