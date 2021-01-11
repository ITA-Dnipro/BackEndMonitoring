#pragma once
#include "stdafx.h"

// This class is the window for the user to send requests to the server and 
// get responses from it
class CConnectorWrapper
{
public:
	CConnectorWrapper();
	void MakeRequest(const std::string& message);
	std::string GetResponse();
	void Connect();

private:
	std::unique_ptr<CConnector> m_connector;
	CInitiationDispatcher* m_dispatcher;

	CClientConnectionHandler* m_handler;
	CSocketWrapper m_stream;
};