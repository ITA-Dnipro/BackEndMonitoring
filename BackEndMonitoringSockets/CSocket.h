#pragma once
#include <iostream>
#include <string>
#include "CBaseSocket.h"

namespace Socket
{
	class CSocket : public BaseSocket::CBaseSocket
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

}
