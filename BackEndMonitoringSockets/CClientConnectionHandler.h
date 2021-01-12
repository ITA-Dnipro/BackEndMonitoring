#pragma once
#include "stdafx.h"
#include "CServiceHandler.h"
#include "CSocketWrapper.h"
// This class handles event form the user
class CClientConnectionHandler : public CServiceHandler
{
public:
	CClientConnectionHandler(int socket);
	void HandleEvent(const int socket, EventType type) override;
	int GetHandle() const override;

private:
	void HandleReadEvent(int socket);
	void HandleWriteEvent(int socket);
	int m_socket;
	std::unique_ptr<CSocketWrapper> m_client_stream;
};
