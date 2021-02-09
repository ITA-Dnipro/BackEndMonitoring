#pragma once
#include "CServiceConnectionHandler.h"
#include "CAcceptor.h"
#include "CSocketWrapper.h"
#include "CThreadPool.h"
#include "CThreadSafeVariable.h"
#include "CDataReceiver.h"

class CEvent;
class CSocketWrapper;

// This class works with server 
class CAcceptorWrapper
{
public:
	CAcceptorWrapper() = delete;
	explicit CAcceptorWrapper(int port, const std::string& ip_address, 
		bool is_blocked, int socket_timeout, CEvent& event);
	CAcceptorWrapper(const CAcceptorWrapper&) = delete;
	CAcceptorWrapper(CAcceptorWrapper&&) noexcept = delete;
	~CAcceptorWrapper();

	bool Initialize(std::shared_ptr<CThreadPool> pool, CDataReceiver& json_data, 
		const int connections);
	bool Execute();
	bool StopSocket();

private:
	void InitAcceptor(int port, const std::string& address);
	void InitServiceHandler(CDataReceiver& json_data);
	void InitSocketWrapper();
	bool HandleEvents();
	void AddClientToThread(int socket_fd);

	std::string m_ip_address;
	std::shared_ptr<CThreadPool> m_p_pool;
	std::unique_ptr<CAcceptor> m_p_server_acceptor;
	std::unique_ptr<CServiceConnectionHandler> m_p_service_handler;
	std::unique_ptr<CSocketWrapper> m_p_stream;
	CEvent& m_event;
	const int m_port;
	int m_socket_timeout;
	bool m_is_socket_blocked;

};

