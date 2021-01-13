#pragma once
#include "stdafx.h"
#include "CConnector.h"
#include "CClientConnectionHandler.h"

// This class is the window for the user to send requests to the server and 
// get responses from it
class CConnectorWrapper
{
public:
	CConnectorWrapper(int port, const std::string& ip_address, 
		std::shared_ptr<CLogger> logger);
	bool MakeRequest();
	bool Connect();

private:
	std::unique_ptr<CConnector> InitConnector(int port, 
		const std::string& ip_address);
	std::unique_ptr<CSocketWrapper> InitStream(int handle);
	std::unique_ptr<CClientConnectionHandler> InitClientHandler(int handle);

	std::unique_ptr<CConnector> m_connector;
	std::unique_ptr<CClientConnectionHandler> m_client_handler;
	std::unique_ptr<CSocketWrapper> m_stream;
	std::shared_ptr<CLogger> m_logger;
};