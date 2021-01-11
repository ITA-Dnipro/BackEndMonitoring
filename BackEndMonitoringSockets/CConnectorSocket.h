#pragma once
#include "CSocket.h"
namespace ConnectorSocket
{
	class CConnectorSocket : public Socket::CSocket
	{
	public:
		CConnectorSocket(const int port, const std::string& ip_address);
		bool Connect();
	};

}
