#pragma once
#include <map>

#include "CEventHandler.h"
#include "CServiceHandler.h"
#include "CInitiationDispatcher.h"
#include "CConnectorSocket.h"

using SockConn = ConnectorSocket::CConnectorSocket;
using CSH = ServiceHandler::CServiceHandler;
using EH = EventHandler::CEventHandler;
using CDispatcher = Dispatcher::CInitiationDispatcher;

namespace Connector
{
	class CConnector : public EventHandler::CEventHandler
	{
	public:
		CConnector(const int port, const std::string& address, CDispatcher* dispathcer);

		void Connect(CSH* handler);
		void HandleEvent(const int socket, EventHandler::EventType type);
		int GetHandle() const;

	protected:
		virtual bool ConnectServiceHandler(CSH* handler);
		//virtual int ActivateServiceHandler(CSH* handler);
		virtual bool Complete(int handle);
		void RegisterHandler(CSH* handler);

	private:
		std::unique_ptr<SockConn> m_socket_connector;
		std::map<int, CSH*> m_connection_map;
		CDispatcher* m_dispatcher;
		int m_port;
		std::string m_ip_address;
	};

}
