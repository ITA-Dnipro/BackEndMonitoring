#pragma once
#include "CServiceHandler.h"
#include "CSocketWrapper.h"
#include "CClientConnectionHandler.h"

class CConnector;

// This class is the window for the user to send requests to the server and 
// get responses from it
class CConnectorWrapper
{
public:
	CConnectorWrapper(int port, const std::string& ip_address);
	~CConnectorWrapper();
	void MakeRequest();

private:
	bool GetRequestConfirmation();
	bool ConnectToServer();
	std::unique_ptr<CConnector> InitConnector(int port, 
		const std::string& ip_address);
	std::unique_ptr<CClientConnectionHandler> InitClientHandler();

	std::unique_ptr<CClientConnectionHandler> m_client_handler;
	std::unique_ptr<CConnector> m_connector;
	std::string m_address;
	int m_port;
};