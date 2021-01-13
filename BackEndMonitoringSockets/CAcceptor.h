#pragma once
#include "stdafx.h"
#include "CAcceptorSocket.h"
#include "CServiceConnectionHandler.h"
#include "CServiceHandler.h"
// Class for accepting connection by the server
class CAcceptor
{
public:
	CAcceptor(const int port, const std::string& ip_address, 
		std::shared_ptr<CLogger> logger);
	int GetConnectedHandle();
	int GetHandle() const;

private:
	std::unique_ptr<CAcceptorSocket> InitAcceptor(const int port, 
		const std::string& ip_address);

	const int m_port;
	std::string m_address;
	std::unique_ptr<CAcceptorSocket> m_peer_acceptor;
	std::shared_ptr<CLogger> m_logger;
};

