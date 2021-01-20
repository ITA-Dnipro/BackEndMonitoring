#pragma once
#include "CConnectorSocket.h"
// This class allows user to connect to the server
class CConnector
{
public:
	CConnector(const int port, const std::string& address, 
		std::shared_ptr<CLogger> logger);

	bool Connect();
	int GetHandle() const;
private:
	std::unique_ptr<CConnectorSocket> InitSocketConnector(const int port, 
		const std::string& ip_address);

	std::unique_ptr<CConnectorSocket> m_socket_connector;
	std::shared_ptr<CLogger> m_logger;
};