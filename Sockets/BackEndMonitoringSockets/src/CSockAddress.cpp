#include "stdafx.h"
#include "CSockAddress.h"
#include "Log.h"

CSockAddress::CSockAddress(const int port, const std::string& ip_address)
	: m_port(port), m_ip_address(ip_address)
{
	InitAddress();
}

sockaddress& CSockAddress::GetSocketAddress()
{
	CLOG_TRACE_START_FUNCTION();
	CLOG_TRACE_END_FUNCTION();
	return m_socket_address;
}

void CSockAddress::InitAddress()
{
	CLOG_DEBUG_START_FUNCTION();
	m_socket_address.sin_family = AF_INET;
	m_socket_address.sin_port = htons(m_port);
	inet_pton(AF_INET, m_ip_address.c_str(), 
		&(m_socket_address.sin_addr.s_addr));
	CLOG_DEBUG_END_FUNCTION();
}
