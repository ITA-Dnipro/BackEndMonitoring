#pragma once
#include "CSocket.h"

// Socket for Acceptor class
class CAcceptorSocket : public CSocket
{
public:
	CAcceptorSocket(const int port, const std::string& ip_address, 
		std::shared_ptr<CLogger> logger);
	int AcceptIncommingCalls();
	bool Open(const int port, const std::string& ip_address);
};

