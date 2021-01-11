#pragma once
#include <iostream>
#include "CServiceHandler.h"
#include "CSocketWrapper.h"
#include "CInitiationDispatcher.h"

using CDispatcher = Dispatcher::CInitiationDispatcher;

namespace ClientConHandler
{
	class CClientConnectionHandler : public ServiceHandler::CServiceHandler
	{
	public:
		CClientConnectionHandler(EventHandler::EventType type, 
			const SocketWrapper::CSocketWrapper& stream, 
			CDispatcher* dispatcher);
		void HandleEvent(const int socket, 
			EventHandler::EventType type) override;
		int GetHandle() const override;

	private:
		SocketWrapper::CSocketWrapper m_client_stream;
	};
}

