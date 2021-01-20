#pragma once
#include "CServiceHandler.h"
#include "CAcceptor.h"
#include "CSocketWrapper.h"
#include "CThreadPool.h"

class DataReceiver;
class CEvent;
class CSocketWrapper;

// This class works with server 
class CAcceptorWrapper
{
public:
	CAcceptorWrapper(int port, const std::string& ip_address, 
		size_t num_threads, CEvent& event);
	void StartServer();
	bool StopSocket();
private:
	std::unique_ptr<CThreadPool> InitThreadPool(size_t num_threads, 
		CEvent& event);
	std::unique_ptr<CAcceptor> InitAcceptor(int port, 
		const std::string& address);
	std::unique_ptr<CServiceHandler> InitServiceHandler();
	std::unique_ptr<CSocketWrapper> InitSocketWrapper();

	CEvent& m_event;
	std::unique_ptr<CThreadPool> m_pool;
	std::unique_ptr<CAcceptor> m_server_acceptor;
	std::unique_ptr<CServiceHandler> m_service_handler;
	std::unique_ptr<CSocketWrapper> m_stream;
};

