#pragma once
#include "CSocket.h"

class CServiceConnectionHandler;
class CServiceHandler;

// Class for accepting connection by the server
class CAcceptor
{
public:
	CAcceptor(const int port, const std::string& ip_address, bool is_blocked);
	int GetConnectedFD();
	int GetHandle() const;
	bool CloseSocket();
private:
	void Initialize();
	bool OpenAcception();
	bool BindSocket();
	bool StartListening();
	bool MakeSocketMulticonnected();
	std::unique_ptr<CSocket> InitSocket(const int port, 
		const std::string& ip_address);

	std::string m_ip_address;
	std::unique_ptr<CSocket> m_socket_acceptor;
	const int m_port;
	bool m_is_socked_blocked;
};

