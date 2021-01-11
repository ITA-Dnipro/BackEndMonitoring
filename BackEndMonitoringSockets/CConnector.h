#pragma once
#include "stdafx.h"
#include "CEventHandler.h"
#include "CInitiationDispatcher.h"
#include "CServiceHandler.h"
#include "CConnectorSocket.h"
// This class allows user to connect to the server
class CConnector : private CEventHandler
{
public:
	CConnector(const int port, const std::string& address,
		CInitiationDispatcher* dispathcer);

	void Connect(CServiceHandler* handler);
	void HandleEvent(const int socket, EventType type) override;
	int GetHandle() const override;

private:
	virtual bool ConnectServiceHandler(CServiceHandler* handler);
	virtual bool Complete(int handle);
	void RegisterHandler(CServiceHandler* handler);


	std::unique_ptr<CConnectorSocket> m_socket_connector;
	std::map<int, CServiceHandler*> m_connection_map;
	CInitiationDispatcher* m_dispatcher;
	int m_port;
	std::string m_ip_address;
};