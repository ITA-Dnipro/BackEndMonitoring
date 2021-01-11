#pragma once
#include "stdafx.h"
#include "CSocket.h"

// Socket for Connector
class CConnectorSocket : public CSocket
{
public:
	CConnectorSocket(const int port, const std::string& ip_address);
	bool Connect();
};