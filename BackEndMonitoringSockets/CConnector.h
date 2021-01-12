#pragma once
#include "stdafx.h"
#include "CServiceHandler.h"
#include "CConnectorSocket.h"
// This class allows user to connect to the server
class CConnector
{
public:
	CConnector(const int port, const std::string& address);

	void Connect();
	int GetHandle() const;
private:
	std::unique_ptr<CConnectorSocket> m_socket_connector;
	std::map<int, CServiceHandler*> m_connection_map;
	int m_port;
	std::string m_ip_address;
};