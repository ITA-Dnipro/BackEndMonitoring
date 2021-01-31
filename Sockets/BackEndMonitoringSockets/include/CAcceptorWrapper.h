#pragma once
#include "CServiceConnectionHandler.h"
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
	CAcceptorWrapper(int port, const std::string& ip_address, CEvent& event, 
		std::shared_ptr<CThreadPool> pool, bool is_blocked, int socket_timeout);
	~CAcceptorWrapper();
	void StartServer();
	bool StopSocket();
private:
	void Initialize(int port, const std::string& ip_address);
	std::unique_ptr<CAcceptor> InitAcceptor(int port, 
		const std::string& address);
	std::unique_ptr<CServiceConnectionHandler> InitServiceHandler();
	std::unique_ptr<CSocketWrapper> InitSocketWrapper();
	void AddClientToThread(int& socket_fd);
	void HandleBlockingEvents();
	void HandleNonBlockingEvents();

	std::shared_ptr<CThreadPool> m_pool;
	std::unique_ptr<CAcceptor> m_server_acceptor;
	std::unique_ptr<CServiceConnectionHandler> m_service_handler;
	std::unique_ptr<CSocketWrapper> m_stream;
	CEvent& m_event;
	int m_socket_timeout;
	bool m_is_socket_blocked;
};

