#pragma once
#include <WinSock2.h>
#include "CEventHandler.h"

using Handler = EventHandler::CEventHandler;

namespace Dispatcher
{
	class IDispatcher
	{
	public:
		virtual void RegisterHandler(Handler* handler, EventHandler::EventType type) = 0;
		virtual void RemoveHandler(Handler* handler, EventHandler::EventType type) = 0;
		virtual void HandleEvents(timeval* timeout = NULL) = 0;
	};

}
