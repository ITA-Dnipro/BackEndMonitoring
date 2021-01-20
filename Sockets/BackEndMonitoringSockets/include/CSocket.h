#pragma once
#include <iostream>
#include "CBaseSocket.h"
// Base class for CAcceptorSocket, CConnectorSocket and CSocketWrapper
class CSocket : public CBaseSocket
{
public:
	CSocket(const int port, const std::string& ip_address, 
		std::shared_ptr<CLogger> logger);
	CSocket(const int socket, std::shared_ptr<CLogger> logger);
	virtual ~CSocket();
	virtual int GetHandle() const;

protected:
	int InitSocket();
	void SetSocketAddress(const int port, const std::string& ip_address);
	bool IsValidSocket() const;
	bool CloseSocket();

	sockaddr_in m_address;
};
