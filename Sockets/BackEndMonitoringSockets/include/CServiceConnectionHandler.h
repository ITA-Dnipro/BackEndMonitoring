#pragma once
#include "CServiceHandler.h"
#include "CSocketWrapper.h"
#include "DataReceiver.h"
// This class handles event form the server
class CServiceConnectionHandler : public CServiceHandler
{
public:
	CServiceConnectionHandler();
	void HandleEvent(const int socket, EventType type) override;

private:
	void HandleRequestEvent(const int client_socket);
	void HandleResponseEvent(const int client_socket);
	std::unique_ptr<CSocketWrapper> InitPeerStream();

	std::unique_ptr<CSocketWrapper> m_peer_stream;
	DataReceiver data;
};