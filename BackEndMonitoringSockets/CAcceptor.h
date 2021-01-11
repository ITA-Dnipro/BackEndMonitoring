#pragma once
#include "stdafx.h"
#include "CEventHandler.h"
#include "CInitiationDispatcher.h"
#include "CAcceptorSocket.h"
#include "CServiceConnectionHandler.h"
#include "CServiceHandler.h"
// Class for accepting connection by the server
class CAcceptor : private CEventHandler
{
public:
	CAcceptor(const int port, const std::string& address,
		CInitiationDispatcher* dispathcer);
	int GetConnectedHandle();
	int GetHandle() const override;
	void HandleEvent(const int socket, EventType type) override;

private:
	const int m_port;
	std::string m_address;
	std::unique_ptr<CAcceptorSocket> m_peer_acceptor;
	CInitiationDispatcher* m_dispatcher;
};

