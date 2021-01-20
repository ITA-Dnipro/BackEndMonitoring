#pragma once
#include "CSocket.h"

class CServiceConnectionHandler;
class CServiceHandler;

// Class for accepting connection by the server
class CAcceptor
{
public:
	CAcceptor(const int port, const std::string& ip_address);
	int GetConnectedHandle();
	int GetHandle() const;
	bool CloseSocket();
private:
	const int SUCCESS = 0;

	bool OpenAcception();
	bool BindSocket();
	bool StartListening();
	std::unique_ptr<CSocket> InitSocket(const int port, 
		const std::string& ip_address);

	const int m_port;
	std::string m_ip_address;
	std::unique_ptr<CSocket> m_socket_acceptor;
};

