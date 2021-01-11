#pragma once
#include "stdafx.h"
#include "CBaseSocket.h"

// Base class for CAcceptorSocket, CConnectorSocket and CSocketWrapper
class CSocket : public CBaseSocket
{
public:
	CSocket(const int port, const std::string& ip_address);
	virtual ~CSocket();

	int GetHandle() const;

protected:
	int InitSocket(const int port, const std::string& ip_address);
	void SetSocketAddress(const int port, const std::string& ip_address);
	bool IsValidSocket() const;
	bool CloseSocket();

	sockaddr_in m_address;
	int m_port;
};
