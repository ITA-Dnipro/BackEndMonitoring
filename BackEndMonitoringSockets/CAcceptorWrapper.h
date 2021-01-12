#pragma once
#include "stdafx.h"
#include "CAcceptor.h"
#include "DataHolder.h"
#include "CServiceConnectionHandler.h"
#include "..\Server\BackEndMonitoringServer\include\CThreadPool.h"
#include "..\Server\BackEndMonitoringServer\include\CEvent.h"
// This class works with server 
class CAcceptorWrapper
{
public:
	CAcceptorWrapper(size_t num_threads, CEvent& event);
	void Start();

private:
	CEvent& m_event;
	std::unique_ptr<CThreadPool> m_pool;
	std::unique_ptr<CAcceptor> m_server_acceptor;
	std::unique_ptr<CServiceConnectionHandler> m_service_handler;
	std::unique_ptr<CSocketWrapper> m_stream;
};

