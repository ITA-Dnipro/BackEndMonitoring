#pragma once
#include "stdafx.h"
#include "CInitiationDispatcher.h"
#include "CServiceHandler.h"
#include "CSocketWrapper.h"
// This class handles event form the server
class CServiceConnectionHandler : public CServiceHandler
{
public:
	CServiceConnectionHandler(const int port, const std::string& ip_address, 
		CInitiationDispatcher* dispatcher);
	void HandleEvent(const int socket, EventType type) override;
	int GetHandle() const override;

private:
	std::unique_ptr<CSocketWrapper> m_peer_stream;
	CInitiationDispatcher* m_dispatcher;
};