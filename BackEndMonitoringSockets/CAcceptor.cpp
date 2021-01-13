#include "stdafx.h"
#include "CAcceptor.h"

CAcceptor::CAcceptor(const int port, const std::string& ip_address,
	std::shared_ptr<CLogger> logger)
	: m_address(ip_address), m_port(port), m_logger(logger)
{
	m_peer_acceptor = InitAcceptor(port, ip_address);
}

int CAcceptor::GetConnectedHandle()
{
	return m_peer_acceptor->AcceptIncommingCalls();
}

int CAcceptor::GetHandle() const
{
	return m_peer_acceptor->GetHandle();
}

std::unique_ptr<CAcceptorSocket> CAcceptor::InitAcceptor(const int port, 
	const std::string& ip_address)
{
	return std::move(std::make_unique<CAcceptorSocket>(port, ip_address, 
		m_logger));
}


