#pragma once
#include "stdafx.h"
#include "CServiceHandler.h"
#include "CSocketWrapper.h"
#include "CInitiationDispatcher.h"
// This class handles event form the user
class CClientConnectionHandler : public CServiceHandler
{
public:
	CClientConnectionHandler(EventType type, const CSocketWrapper& stream,
		CInitiationDispatcher* dispatcher);
	void HandleEvent(const int socket, EventType type) override;
	int GetHandle() const override;

private:
	CSocketWrapper m_client_stream;
};
