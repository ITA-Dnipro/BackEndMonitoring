#pragma once
#include "CServiceHandler.h"
#include "CSocketWrapper.h"
#include "DataReceiver.h"

// This class handles event form the server
class CServiceConnectionHandler : public CServiceHandler
{
public:
	CServiceConnectionHandler();
	bool HandleEvent(const int socket, EventType type) override;

private:
	bool HandleRequestEvent(const int socket_fd);
	bool HandleResponseEvent(const int socket_fd);
	bool HandleResponseExitEvent(const int socket_fd);
	std::unique_ptr<CSocketWrapper> InitPeerStream();

	std::unique_ptr<CSocketWrapper> m_peer_stream;
	DataReceiver data;
};