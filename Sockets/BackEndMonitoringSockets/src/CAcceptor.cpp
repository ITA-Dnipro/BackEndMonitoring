#include "stdafx.h"
#include "CAcceptor.h"
#include "CServiceConnectionHandler.h"
#include "CServiceHandler.h"
#include "CLogger/include/Log.h"


CAcceptor::CAcceptor(const int port, const std::string& ip_address, 
	bool is_blocked) : m_ip_address(ip_address), m_port(port),
	m_is_socked_blocked(is_blocked)
{
	Initialize();
	MakeSocketMulticonnected();
}

int CAcceptor::GetConnectedFD()
{
	sockaddress current_address = m_socket_acceptor->GetSocketAddress();
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_WITH_PARAMS("In the class CAcceptor was accepted socket ",
		m_socket_acceptor->GetSocketFD());
	
	CLOG_DEBUG_END_FUNCTION();
	return PlatformUtils::Accept(m_socket_acceptor->GetSocketFD(), 
		current_address);
}

int CAcceptor::GetHandle() const
{
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_WITH_PARAMS("Retrun socket descriptor ", 
		m_socket_acceptor->GetSocketFD());
	CLOG_DEBUG_END_FUNCTION();
	return m_socket_acceptor->GetSocketFD();
}

bool CAcceptor::CloseSocket()
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_WITH_PARAMS("Try close socket descriptor ",
	m_socket_acceptor->GetSocketFD());
	if (m_socket_acceptor->CloseSocket())
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

void CAcceptor::Initialize()
{
	CLOG_DEBUG_START_FUNCTION();
	InitSocket(m_port, m_ip_address);

	if (OpenAcception() && !m_is_socked_blocked)
	{
		PlatformUtils::SetUnblockingSocket(m_socket_acceptor->GetSocketFD());
	}
	CLOG_DEBUG_END_FUNCTION();
}

bool CAcceptor::OpenAcception()
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	if (BindSocket() && StartListening())
	{
		result = true;
	}
	CLOG_DEBUG_WITH_PARAMS("Result of work function  OpenAcception", result);
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

bool CAcceptor::BindSocket()
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	sockaddress current_address = m_socket_acceptor->GetSocketAddress();
	result = PlatformUtils::BindSocket(m_socket_acceptor->GetSocketFD(), 
		current_address);
	CLOG_DEBUG_WITH_PARAMS("Bind socket returned ", result);
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

bool CAcceptor::StartListening()
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	result = PlatformUtils::Listen(m_socket_acceptor->GetSocketFD());
	CLOG_DEBUG_WITH_PARAMS("Listen socket returned ", result);
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

bool CAcceptor::MakeSocketMulticonnected()
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	int on = 1;
	if (setsockopt(m_socket_acceptor->GetSocketFD(), SOL_SOCKET, SO_REUSEADDR,
		(char*)&on, sizeof(on)) != ERROR_SOCKET)
	{
		CLOG_DEBUG_WITH_PARAMS("setsockopt was successful, the socket ", 
			m_socket_acceptor->GetSocketFD(), " was made multiconnected");
		result = true;
	}
	CLOG_DEBUG("setsockopt returned -1");
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

void CAcceptor::InitSocket(const int port,
	const std::string& ip_address)
{
	CLOG_DEBUG_START_FUNCTION();
	m_socket_acceptor = std::make_unique<CSocket>(port, ip_address);
	CLOG_TRACE_VAR_CREATION(m_socket_acceptor);
	CLOG_DEBUG_END_FUNCTION();
}


