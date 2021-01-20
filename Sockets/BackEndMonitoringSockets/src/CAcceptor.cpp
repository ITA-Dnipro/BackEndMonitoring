#include "stdafx.h"
#include "CAcceptor.h"
#include "CServiceConnectionHandler.h"
#include "CServiceHandler.h"

CAcceptor::CAcceptor(const int port, const std::string& ip_address)
	: m_ip_address(ip_address), m_port(port)
{
	m_socket_acceptor = InitSocket(port, ip_address);
	OpenAcception();
}

int CAcceptor::GetConnectedHandle()
{
	return static_cast<int>(accept(m_socket_acceptor->GetHandle(), NULL, NULL));
}

int CAcceptor::GetHandle() const
{
	return m_socket_acceptor->GetHandle();
}

bool CAcceptor::CloseSocket()
{
	return m_socket_acceptor->CloseSocket();
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
	sockaddr_in current_address = m_socket_acceptor->GetSocketAddress();
	if (::bind(m_socket_acceptor->GetHandle(), (SOCKADDR*)&current_address, 
		sizeof(current_address)) == SUCCESS)
	{
		return true;
	}
	return false;
}

bool CAcceptor::StartListening()
{
	if (::listen(m_socket_acceptor->GetHandle(), SOMAXCONN) == SUCCESS)
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


