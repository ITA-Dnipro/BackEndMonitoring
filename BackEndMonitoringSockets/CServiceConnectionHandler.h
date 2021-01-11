#pragma once
#include <memory>

#include "CServiceHandler.h"
#include "CSocketWrapper.h"
#include "CInitiationDispatcher.h"
#include "CAcceptor.h"

using CStream = SocketWrapper::CSocketWrapper;
using CDispatcher = Dispatcher::CInitiationDispatcher;

namespace ServiceConHandler
{
	class CServiceConnectionHandler : public ServiceHandler::CServiceHandler
	{
	public:
		CServiceConnectionHandler(const int port, 
			const std::string& ip_address, 
			CDispatcher* dispatcher);
		void HandleEvent(const int socket, 
			EventHandler::EventType type) override;
		int GetHandle() const override;

	private:
		std::unique_ptr<CStream> m_peer_stream;
		CDispatcher* m_dispatcher;
	};

}
