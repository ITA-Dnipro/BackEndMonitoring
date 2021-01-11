#pragma once
#include "stdafx.h"
#include "IDispatcher.h"
#include "CEventHandlerStorage.h"
// Class stores events in the storage and allow to handle them
class CInitiationDispatcher : public IDispatcher
{
public:
	static CInitiationDispatcher* GetInstance();
	void RegisterHandler(CEventHandler* handler, EventType type) override;
	void RemoveHandler(CEventHandler* handler, EventType type) override;
	void HandleEvents(timeval* timeout = NULL) override;

private:
	explicit CInitiationDispatcher();
	static CInitiationDispatcher* s_instance;

	CEventHandlerStorage m_storage;
};