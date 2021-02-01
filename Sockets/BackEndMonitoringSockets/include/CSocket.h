#pragma once
#include "PlatformUtils.h"

class CSocket : public CBaseSocket
{
public:
	CSocket(const int port, const std::string& ip_address);
	bool CloseSocket();
	sockaddress GetSocketAddress() const;

protected:
	void SetSocketAddress(const int port, const std::string& ip_address);
	bool IsValidSocket() const;
	
};
