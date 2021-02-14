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
	~CAcceptor() noexcept;

	bool Initialize(const std::string& ip_address, const int listener_port, 
		const int connections);
	bool AcceptNewClient(CSocket& client);
	bool IsTimeOutWithoutConnections() const;

private:
	bool BindSocket() const;
	bool StartListening(const int connections) const;
	bool MakeSocketMulticonnected() const;
	bool InitSocket(const int port, const std::string& ip_address);
	bool AcceptNonBlockingSockets(CSocket& client);
	bool AcceptBlockingSockets(CSocket& client);

	std::unique_ptr<CSocket> m_p_socket_acceptor;
	CEvent& m_event;
	int m_socket_timeout;
	bool m_is_socket_blocked;
	bool m_is_acceptor_initialized;
	bool m_is_time_out;
};

