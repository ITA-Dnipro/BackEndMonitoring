#pragma once
class CEvent;
class CSocketWrapper;
class CAcceptor;
class CServiceConnectionHandler;
class CThreadPool;
class CDataReceiver;
class CSocket;

// This class works with server 
class CServiceHost
{	
public:
	CServiceHost() = delete;
	explicit CServiceHost(int port, const std::string& ip_address, 
		bool is_blocked, int socket_timeout, CEvent& event);
	CServiceHost(const CServiceHost&) = delete;
	CServiceHost(CServiceHost&&) noexcept = delete;
	~CServiceHost();

	bool Initialize(std::shared_ptr<CThreadPool> pool, CDataReceiver& json_data, 
		const int connections);
	bool Execute();
	void ShutDown();

private:
	void InitAcceptor();
	void InitServiceHandler(CDataReceiver& json_data);
	void InitSocketWrapper();
	bool HandleEvents();
	void AcceptRequest();
	void AddClientToThread(const CSocket& client);
	bool DeleteBrokenSocket(const int socket_fd);
	void AcceptClients();
	void DeleteAllClients();
	
	std::mutex m_mutex;
	std::string m_ip_address;
	std::list<std::pair<CSocket, bool>> m_clients_statuses;
	std::shared_ptr<CThreadPool> m_p_pool;
	std::unique_ptr<CAcceptor> m_p_server_acceptor;
	std::unique_ptr<CServiceConnectionHandler> m_p_service_handler;
	std::unique_ptr<CSocketWrapper> m_p_stream;
	CEvent& m_event;
	const int m_port;
	int m_socket_timeout;
	bool m_is_socket_blocked;
	bool m_is_host_initialized;
};

