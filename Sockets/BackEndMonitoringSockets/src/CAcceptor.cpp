#include "stdafx.h"

#include "CAcceptor.h"
#include "CServiceConnectionHandler.h"
#include "EEventType.h"
#include "CLogger/include/Log.h"
#include "CEvent.h"

CAcceptor::CAcceptor(bool is_blocked, int socket_timeout, CEvent& event)
	: m_is_socket_blocked(is_blocked), m_socket_timeout(socket_timeout),
	m_event(event), m_port(c_not_initialized_port),
	m_is_acceptor_initialized(false), m_is_time_out(false)
{ }

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
			m_is_acceptor_initialized =
				PlatformUtils::SetUnblockingSocket
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

bool CAcceptor::Accept(int& connected_socket_fd)
{
	CLOG_TRACE_START_FUNCTION();
	connected_socket_fd = c_error_socket;

	if (m_is_acceptor_initialized)
	{
		while (!m_event.WaitFor(std::chrono::nanoseconds(1000)))
		{
			if (m_is_socket_blocked)
			{
				connected_socket_fd = AcceptBlockingSockets();
			}
			else
			{
				connected_socket_fd = AcceptNonBlockingSockets();
			}

			if (connected_socket_fd > 0)
			{
				CLOG_DEBUG_WITH_PARAMS("Acctpted socket ", connected_socket_fd);
				return true;
			}
			else if (connected_socket_fd == c_error_socket)
			{
				return false;
			}
		}

	}
	CLOG_TRACE_END_FUNCTION();
	return false;
}

bool CAcceptor::IsTimeOutWithoutConnections()
{
	return m_is_time_out;
}

bool CAcceptor::CloseSocket()
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_WITH_PARAMS("Try close socket descriptor ",
	m_p_socket_acceptor->GetSocketFD());
	if (m_p_socket_acceptor->CloseSocket())
	{
		result = true;
		CLOG_DEBUG_WITH_PARAMS("Socket was succesfully closed, result of the function - ",
			result);
	}
	CLOG_DEBUG_WITH_PARAMS("Cannot close socket, result of the function - ",
		result);
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

bool CAcceptor::BindSocket()
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	sockaddress current_address = m_p_socket_acceptor->GetSocketAddress();
	result = PlatformUtils::BindSocket(m_p_socket_acceptor->GetSocketFD(),
		current_address);
	CLOG_DEBUG_WITH_PARAMS("Bind socket returned ", result);
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

bool CAcceptor::StartListening(const int connections)
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	result = PlatformUtils::Listen(m_p_socket_acceptor->GetSocketFD(),
		connections);
	CLOG_DEBUG_WITH_PARAMS("Listen socket returned ", result);
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

bool CAcceptor::MakeSocketMulticonnected()
{
	CLOG_DEBUG_START_FUNCTION();
	int on = 1;
	if (setsockopt(m_p_socket_acceptor->GetSocketFD(), SOL_SOCKET, SO_REUSEADDR,
		(char*)&on, sizeof(on)) != c_error_socket)
	{
		CLOG_DEBUG_WITH_PARAMS("Setsockopt was successful, the socket ",
			m_p_socket_acceptor->GetSocketFD(), " was made multiconnected");
		return true;
	}
	CLOG_DEBUG("Setsockopt returned -1");
	CLOG_DEBUG_END_FUNCTION();
	return false;
}

void CAcceptor::InitSocket(const int port,
	const std::string& ip_address)
{
	CLOG_DEBUG_START_FUNCTION();
	m_p_socket_acceptor = std::make_unique<CSocket>(port, ip_address);
	CLOG_TRACE_VAR_CREATION(m_p_socket_acceptor);
	CLOG_DEBUG_END_FUNCTION();
}

int CAcceptor::AcceptNonBlockingSockets()
{
	sockaddress current_address = m_p_socket_acceptor->GetSocketAddress();
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_WITH_PARAMS("In the class CAcceptor was accepted socket ",
		m_p_socket_acceptor->GetSocketFD());

	CLOG_DEBUG_END_FUNCTION();
	return PlatformUtils::Accept(m_p_socket_acceptor->GetSocketFD(),
		current_address);
}

int CAcceptor::AcceptBlockingSockets()
{
	CLOG_TRACE_START_FUNCTION();
	int max_sd = 0;
	fd_set read_fds;
	int socket_fd = c_error_socket;
	timeval time_out;

	sockaddress current_address = m_p_socket_acceptor->GetSocketAddress();

	while (!m_event.WaitFor(std::chrono::nanoseconds(1000)))
	{
		FD_ZERO(&read_fds);
		time_out.tv_sec = m_socket_timeout;

		FD_SET(m_p_socket_acceptor->GetSocketFD(), &read_fds);
		max_sd = m_p_socket_acceptor->GetSocketFD();

		select(max_sd + 1, &read_fds, NULL, NULL, &time_out);

		if (FD_ISSET(m_p_socket_acceptor->GetSocketFD(), &read_fds))
		{
			CLOG_DEBUG_WITH_PARAMS("FD_ISSET reacted to the event in the socket ",
				m_p_socket_acceptor->GetSocketFD());
			return PlatformUtils::Accept(m_p_socket_acceptor->GetSocketFD(),
				current_address);
		}
		else
		{
			m_is_time_out = true;
			return c_error_socket;
		}
	}
	CLOG_TRACE_END_FUNCTION();
	return c_error_socket;
}
