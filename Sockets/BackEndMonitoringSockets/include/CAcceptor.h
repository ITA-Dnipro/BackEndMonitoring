#pragma once
#include "CSocket.h"

class CServiceConnectionHandler;
class CServiceHandler;
class CEvent;
// Class for accepting connection by the server
class CAcceptor
{
public:
	CAcceptor() = delete;
	explicit CAcceptor(bool is_blocked, int socket_timeout, CEvent& event);
	CAcceptor(const CAcceptor&) = delete;
	CAcceptor(CAcceptor&&) noexcept = delete;
	~CAcceptor() noexcept = default;

	bool Initialize(const std::string& ip_address, const int listener_port, 
		const int connections);
	bool AcceptNewClient(int& socket_fd);
	//bool AcceptRequest(int& socket_fd);
	bool IsTimeOutWithoutConnections();
	bool CloseSocket();
	//bool DeleteClient(int socket_fd);

private:
	const int c_not_initialized_port = 0;

	bool BindSocket();
	bool StartListening(const int connections);
	bool MakeSocketMulticonnected();
	void InitSocket(const int port, const std::string& ip_address);
	[[nodiscard]] int AcceptNonBlockingSockets();
	[[nodiscard]] int AcceptBlockingSockets();

	std::string m_ip_address;
	//std::vector<int> m_accepted_clients;
	std::unique_ptr<CSocket> m_p_socket_acceptor;
	CEvent& m_event;
	const int m_port;
	int m_socket_timeout;
	bool m_is_socket_blocked;
	bool m_is_acceptor_initialized;
	bool m_is_time_out;
};

