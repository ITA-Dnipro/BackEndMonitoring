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
	//CLOG_DEBUG_WITH_PARAMS("In the class CAcceptor was accepted socket ",
		//socket_fd);
	
	return PlatformUtils::Accept(m_socket_acceptor->GetSocketFD());
}

int CAcceptor::GetHandle() const
{
	return m_socket_acceptor->GetSocketFD();
}

bool CAcceptor::CloseSocket()
{
	if (m_socket_acceptor->CloseSocket())
	{
		CLOG_DEBUG("Socket was succesfully closed");
		return true;
	}
	CLOG_DEBUG("Cannot close socket");
	return false;
}

void CAcceptor::Initialize()
{
	m_socket_acceptor = InitSocket(m_port, m_ip_address);

	if (OpenAcception())
	{
		// log pos
	}
	else
	{
		//log neg
	}

	if (!m_is_socked_blocked)
	{
		PlatformUtils::SetUnblockingSocket(m_socket_acceptor->GetSocketFD());
	}
}

bool CAcceptor::OpenAcception()
{
	if (BindSocket() && StartListening())
	{
		return true;
	}
	return false;
}

bool CAcceptor::BindSocket()
{
	sockaddress current_address = m_socket_acceptor->GetSocketAddress();
	return PlatformUtils::BindSocket(m_socket_acceptor->GetSocketFD(), current_address);
}

bool CAcceptor::StartListening()
{
	return PlatformUtils::Listen(m_socket_acceptor->GetSocketFD());
}

bool CAcceptor::MakeSocketMulticonnected()
{
	int on = 1;
	if (setsockopt(m_socket_acceptor->GetSocketFD(), SOL_SOCKET, SO_REUSEADDR,
		(char*)&on, sizeof(on)) != ERROR_SOCKET)
	{
		return true;
	}
	return false;
}

std::unique_ptr<CSocket> CAcceptor::InitSocket(const int port,
	const std::string& ip_address)
{
	return std::move(std::make_unique<CSocket>(port, ip_address));
}


