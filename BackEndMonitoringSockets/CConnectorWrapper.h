#pragma once
#include "stdafx.h"
#include "CConnector.h"
#include "CClientConnectionHandler.h"

// This class is the window for the user to send requests to the server and 
// get responses from it
class CConnectorWrapper
{
public:
	CConnectorWrapper();
	void MakeRequest(const std::string& message);
	//std::string GetResponse();
	void Connect();

private:
	std::unique_ptr<CConnector> InitConnector();
	std::unique_ptr<CSocketWrapper> InitStream(int handle);

	std::unique_ptr<CConnector> m_connector;
	std::unique_ptr<CClientConnectionHandler> m_client_handler;
	std::unique_ptr<CSocketWrapper> m_stream;
};