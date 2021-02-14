#include "stdafx.h"

#include "CAcceptor.h"
#include "CLogger/include/Log.h"
#include "CEvent.h"

CAcceptor::CAcceptor(bool is_blocked, int socket_timeout, CEvent& event)
	: m_is_socket_blocked(is_blocked), m_socket_timeout(socket_timeout),
	m_event(event), m_is_acceptor_initialized(false), m_is_time_out(false)
{ }

CAcceptor::~CAcceptor() noexcept
{
	PlatformUtils::CloseSocket(m_p_socket_acceptor->GetSocketFD());
}

bool CAcceptor::Initialize(const std::string& ip_address,
                           const int listener_port, const int connections)
{
	CLOG_DEBUG_START_FUNCTION();

	InitSocket(listener_port, ip_address);

	if (MakeSocketMulticonnected() && BindSocket() &&
		StartListening(connections))
	{
		if (!m_is_socket_blocked)
		{
			CLOG_DEBUG("Set unblocking socket");
			m_is_acceptor_initialized = PlatformUtils::SetUnblockingSocket
				(m_p_socket_acceptor->GetSocketFD());
		}
		else
		{
			m_is_acceptor_initialized = true;
		}
		CLOG_DEBUG_WITH_PARAMS("m_is_acceptor_initialized equal ",
			m_is_acceptor_initialized);
	}
	CLOG_DEBUG_END_FUNCTION();
	return m_is_acceptor_initialized;
}

bool CAcceptor::AcceptNewClient(CSocket& client)
{
	if (m_is_acceptor_initialized)
	{
		if (m_is_socket_blocked)
		{
			return AcceptBlockingSockets(client);
		}
		else
		{
			return AcceptNonBlockingSockets(client);
		}
	}
	return false;
}

bool CAcceptor::IsTimeOutWithoutConnections() const
{
	return m_is_time_out;
}

bool CAcceptor::BindSocket() const
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	sockaddress current_address = m_p_socket_acceptor->GetSocketAddress();
	result = PlatformUtils::BindSocket(m_p_socket_acceptor->GetSocketFD(),
		current_address);
	CLOG_DEBUG_WITH_PARAMS("Bind socket returned", result);
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

bool CAcceptor::StartListening(const int connections) const
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	result = PlatformUtils::Listen(m_p_socket_acceptor->GetSocketFD(),
		connections);
	CLOG_DEBUG_WITH_PARAMS("Listen socket returned", result);
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

bool CAcceptor::MakeSocketMulticonnected() const
{
	CLOG_DEBUG_START_FUNCTION();
	int on = 1;
	if (setsockopt(m_p_socket_acceptor->GetSocketFD(), SOL_SOCKET, SO_REUSEADDR,
		(char*)&on, sizeof(on)) != c_error_socket)
	{
		CLOG_DEBUG_WITH_PARAMS("Setsockopt was successful, the socket",
			m_p_socket_acceptor->GetSocketFD(), "was made multiconnected");
		return true;
	}
	CLOG_DEBUG("Setsockopt failed");
	CLOG_DEBUG_END_FUNCTION();
	return false;
}

bool CAcceptor::InitSocket(const int port,
	const std::string& ip_address)
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	m_p_socket_acceptor = std::make_unique<CSocket>(port, ip_address);
	CLOG_TRACE_VAR_CREATION(m_p_socket_acceptor);
	result = m_p_socket_acceptor->InitSocket();
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

bool CAcceptor::AcceptNonBlockingSockets(CSocket& client)
{
	bool result = false;
	sockaddress current_address = m_p_socket_acceptor->GetSocketAddress();
	result = PlatformUtils::Accept(m_p_socket_acceptor->GetSocketFD(), client);
	if (client.IsValidSocket())
	{
		CLOG_DEBUG_WITH_PARAMS("In the class CAcceptor was accepted socket ",
			client.GetSocketFD());
		return true;
	}
	return false;
}

bool CAcceptor::AcceptBlockingSockets(CSocket& client)
{
	CLOG_TRACE_START_FUNCTION();
	m_is_time_out = false;
	int max_sd = 0;
	int result_of_select = 0;
	fd_set read_fds;
	timeval time_out;

	sockaddress current_address = m_p_socket_acceptor->GetSocketAddress();

	while (!m_event.WaitFor(std::chrono::nanoseconds(1000)))
	{
		FD_ZERO(&read_fds);
		time_out.tv_sec = m_socket_timeout;

		FD_SET(m_p_socket_acceptor->GetSocketFD(), &read_fds);
		max_sd = m_p_socket_acceptor->GetSocketFD();

		result_of_select = select(max_sd + 1, &read_fds, NULL, 
			NULL, &time_out);
		if(result_of_select < 0)
		{
			return false;
		}
		else if(result_of_select == 0)
		{
			m_is_time_out = true;
			return false;
		}

		if (FD_ISSET(m_p_socket_acceptor->GetSocketFD(), &read_fds))
		{
			CLOG_DEBUG_WITH_PARAMS("FD_ISSET reacted to the event in the socket ",
				m_p_socket_acceptor->GetSocketFD());
			return PlatformUtils::Accept(m_p_socket_acceptor->GetSocketFD(), client);
		}
	}
	CLOG_TRACE_END_FUNCTION();
	return false;
}
