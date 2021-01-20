#pragma once
#include "CSocket.h"

// Socket for Connector
class CConnectorSocket : public CSocket
{
public:
	CConnectorSocket(const int port, const std::string& ip_address, 
		std::shared_ptr<CLogger> logger);
	bool Connect();
};