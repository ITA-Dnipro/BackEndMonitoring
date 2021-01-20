#pragma once
#include "CSocket.h"

// This class allows user to connect to the server
class CConnector
{
public:
	CConnector(const int port, const std::string& address);

	bool Connect();
	int GetHandle() const;
private:
	std::unique_ptr<CSocket> InitSocketConnector(const int port, 
		const std::string& ip_address);

	std::unique_ptr<CSocket> m_socket_connector;
};