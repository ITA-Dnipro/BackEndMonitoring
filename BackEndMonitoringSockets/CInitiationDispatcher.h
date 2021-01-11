#pragma once
#include <iostream>
#include "IDispatcher.h"

#include "CEventHandlerStorage.h"

using CStorage = Storage::CEventHandlerStorage;
namespace Dispatcher
{
	class CInitiationDispatcher : public Dispatcher::IDispatcher
	{
	public:
		static CInitiationDispatcher* GetInstance();
		void RegisterHandler(Handler* handler, 
			EventHandler::EventType type) override; 
		void RemoveHandler(Handler* handler, 
			EventHandler::EventType type) override;
		void HandleEvents(timeval* timeout = NULL) override;

	private:
		CInitiationDispatcher();
		static CInitiationDispatcher* m_instance;

		CStorage m_storage;
	};

}
