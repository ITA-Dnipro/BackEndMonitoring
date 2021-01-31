#pragma once
#include "CServiceHandler.h"
#include "CSocketWrapper.h"
#include "CServerResponseHolder.h"

// This class handles event form the user
class CClientConnectionHandler : public CServiceHandler
{
public:
	CClientConnectionHandler();
	bool HandleEvent(const int socket, EventType type) override;

private:
	bool HandleRequestEvent(const int socket,
							EventType type);
	bool HandleResponseEvent(const int socket);
	bool HandleExitEvent(const int socket);
	std::unique_ptr<CSocketWrapper> InitClientStream();

	std::unique_ptr<CSocketWrapper> m_client_stream;
	CServerResponseHolder m_response_holder;
};
