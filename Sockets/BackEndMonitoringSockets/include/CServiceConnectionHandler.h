#pragma once
#include "CServiceHandler.h"
#include "CSocketWrapper.h"
#include "CDataReceiver.h"

enum class EClientRequestType;

// This class handles event form the server
class CServiceConnectionHandler : public CServiceHandler
{
public:
	CServiceConnectionHandler(CDataReceiver json_data);
	bool HandleEvent(const int socket, EventType type) override;

private:
	bool HandleRequestEvent(const int socket_fd);
	bool HandleResponseEvent(const int socket_fd,
		EClientRequestType type);
	bool HandleResponseExitEvent(const int socket_fd);
	std::unique_ptr<CSocketWrapper> InitPeerStream();

	CDataReceiver m_json_data;
	std::unique_ptr<CSocketWrapper> m_peer_stream;
};