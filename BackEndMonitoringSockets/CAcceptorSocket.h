#pragma once
#include "stdafx.h"
#include "CSocket.h"

// Socket for Acceptor class
class CAcceptorSocket : public CSocket
{
public:
	CAcceptorSocket(const int port, const std::string& ip_address);
	int AcceptIncommingCalls();
	bool Open(const int port, const std::string& ip_address);

private:
};

