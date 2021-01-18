#pragma once
#include "CAcceptor.h"
#include "DataReceiver.h"
#include "CServiceConnectionHandler.h"
#include "CThreadPool.h"
#include "CEvent.h"

// This class works with server 
class CAcceptorWrapper
{
public:
	CAcceptorWrapper(int port, const std::string& ip_address, 
		size_t num_threads, CEvent& event, std::shared_ptr<CLogger> logger);
	void StartServer();

private:
	std::unique_ptr<CThreadPool> InitThreadPool(int num_threads, CEvent& event);
	std::unique_ptr<CAcceptor> InitAcceptor(int port, 
		const std::string& address);
	std::unique_ptr<CServiceConnectionHandler> InitServiceHandler(int handle);
	std::unique_ptr<CSocketWrapper> InitSocketWrapper(int handle);

	CEvent& m_event;
	std::unique_ptr<CThreadPool> m_pool;
	std::unique_ptr<CAcceptor> m_server_acceptor;
	std::unique_ptr<CServiceConnectionHandler> m_service_handler;
	std::unique_ptr<CSocketWrapper> m_stream;
	std::shared_ptr<CLogger> m_logger;
};

