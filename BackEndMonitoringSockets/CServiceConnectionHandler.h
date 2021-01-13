#pragma once
#include "stdafx.h"
#include "CServiceHandler.h"
#include "CSocketWrapper.h"
#include "DataHolder.h"
// This class handles event form the server
class CServiceConnectionHandler : public CServiceHandler
{
public:
	CServiceConnectionHandler(int socket, std::shared_ptr<CLogger> logger);
	void HandleEvent(const int socket, EventType type) override;
	int GetHandle() const override;

private:
	void HandleRequestEvent(const int client_socket);
	void HandleResponseEvent(const int client_socket);
	std::unique_ptr<CSocketWrapper> InitPeerStream(int handle);

	std::unique_ptr<CSocketWrapper> m_peer_stream;
	int m_server_socket;
	DataHolder data;
	std::shared_ptr<CLogger> m_logger;
};