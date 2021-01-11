#pragma once
#include "CEventHandler.h"
#include "CServiceHandler.h"
#include "CAcceptorSocket.h"
#include "CInitiationDispatcher.h"
#include "CServiceConnectionHandler.h"

using CDispatcher = Dispatcher::CInitiationDispatcher;

namespace Acceptor
{
	class CAcceptor : public EventHandler::CEventHandler
	{
	public:
		CAcceptor(const int port, const std::string& address, CDispatcher* dispathcer);
		bool Listening();
		int GetHandle() const override;
		void HandleEvent(const int socket, EventHandler::EventType type) override;

	private:
		const int m_port;
		std::string m_address;
		std::unique_ptr<AcceptorSocket::CAcceptorSocket> m_peer_acceptor;
		CDispatcher* m_dispatcher;
	};
}

