#pragma once
#include "stdafx.h"
#include "CAcceptorSocket.h"
#include "CServiceConnectionHandler.h"
#include "CServiceHandler.h"
// Class for accepting connection by the server
class CAcceptor
{
public:
	CAcceptor(const int port, const std::string& address);
	int GetConnectedHandle();
	int GetHandle() const;
	void HandleEvent(const int socket, EventType type);

private:
	const int m_port;
	std::string m_address;
	std::unique_ptr<CAcceptorSocket> m_peer_acceptor;
};

