#pragma once
#include "CServiceHandler.h"
#include "CSocketWrapper.h"

// This class handles event form the user
class CClientConnectionHandler : public CServiceHandler
{
public:
	CClientConnectionHandler();
	void HandleEvent(const int socket, EventType type) override;

private:
	void HandleReadEvent(int socket);
	void HandleWriteEvent(int socket);
	std::unique_ptr<CSocketWrapper> InitClientStream();

	std::unique_ptr<CSocketWrapper> m_client_stream;
};
