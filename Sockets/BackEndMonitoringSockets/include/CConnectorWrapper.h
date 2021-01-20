#pragma once
#include "CServiceHandler.h"
#include "CSocketWrapper.h"

class CConnector;

// This class is the window for the user to send requests to the server and 
// get responses from it
class CConnectorWrapper
{
public:
	CConnectorWrapper(int port, const std::string& ip_address);
	void MakeRequest();

private:
	bool GetRequestConfirmation();
	bool ConnectToServer(std::unique_ptr<CConnector> connector);
	std::unique_ptr<CConnector> InitConnector(int port, 
		const std::string& ip_address);
	std::unique_ptr<CServiceHandler> InitClientHandler();

	int m_port;
	std::string m_address;
	std::unique_ptr<CServiceHandler> m_client_handler;
};