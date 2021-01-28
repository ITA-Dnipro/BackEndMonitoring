#pragma once
#include "CServiceHandler.h"
#include "CSocketWrapper.h"
#include "CClientConnectionHandler.h"
#include "CServerResponseHolder.h"

class CConnector;

// This class is the window for the user to send requests to the server and 
// get responses from it
class CConnectorWrapper
{
public:
	CConnectorWrapper(int port, const std::string& ip_address);
	~CConnectorWrapper();

	std::string MakeRequest() const;
	bool ConnectToServer() const;
	void Exit();

private:
	std::unique_ptr<CConnector> InitConnector(int port, 
		const std::string& ip_address);
	std::unique_ptr<CClientConnectionHandler> InitClientHandler();

	std::string m_address;
	std::unique_ptr<CClientConnectionHandler> m_client_handler;
	std::unique_ptr<CConnector> m_connector;
	CServerResponseHolder m_response_holder;
	int m_port;
};