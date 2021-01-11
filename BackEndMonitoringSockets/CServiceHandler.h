#pragma once
#include "CEventHandler.h"

namespace ServiceHandler
{
	class CServiceHandler : public EventHandler::CEventHandler
	{
	public:
		virtual void HandleEvent(int socket, EventHandler::EventType type) = 0;
		virtual int GetHandle() const = 0;
	};
}
