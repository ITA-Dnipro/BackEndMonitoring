#pragma once
#include "CConnector.h"
#include "CClientConnectionHandler.h"

// This class is the window for the user to send requests to the server and 
// get responses from it
class CConnectorWrapper
{
public:
	CConnectorWrapper(int port, const std::string& ip_address, 
		std::shared_ptr<CLogger> logger);
	void MakeRequest();

private:
	bool GetRequestConfirmation();
	bool ConnectToServer(std::unique_ptr<CConnector> connector,
		std::unique_ptr<CClientConnectionHandler> client_handler);
	std::unique_ptr<CConnector> InitConnector(int port, 
		const std::string& ip_address);
	std::unique_ptr<CClientConnectionHandler> InitClientHandler(int handle);

	int m_port;
	std::string m_address;
	std::shared_ptr<CLogger> m_logger;
};