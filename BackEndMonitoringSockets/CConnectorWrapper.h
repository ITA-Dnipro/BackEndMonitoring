#pragma once
#include "CClientConnectionHandler.h"
#include "CInitiationDispatcher.h"
#include "CConnector.h"
#include "CSocketWrapper.h"

using Stream = SocketWrapper::CSocketWrapper;
using ClientHandler = ClientConHandler::CClientConnectionHandler;
using CDispatcher = Dispatcher::CInitiationDispatcher;


namespace ConnectorWrapper
{
	class CConnectorWrapper
	{
	public:
		CConnectorWrapper();
		void MakeRequest(const std::string& message);
		std::string GetResponse();
		void Connect();

	private:
		std::unique_ptr<Connector::CConnector> m_connector;
		CDispatcher* m_dispatcher;

		ClientHandler* m_handler;
		Stream m_stream;
	};

}
