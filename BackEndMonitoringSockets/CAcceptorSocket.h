#pragma once
#include "CSocket.h"

namespace AcceptorSocket
{
	class CAcceptorSocket : public Socket::CSocket
	{
	public:
		CAcceptorSocket(const int port, const std::string& ip_address);
		int AcceptIncommingCalls();
		bool Open(const int port, const std::string& ip_address);

	private:
	};
}

