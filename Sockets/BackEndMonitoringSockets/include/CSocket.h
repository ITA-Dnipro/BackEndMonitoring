#pragma once
#include "PlatformUtils.h"

class CSocket : public CBaseSocket
{
public:
	CSocket(const int port, const std::string& ip_address);
	virtual int GetSocket_fd() const;
	bool CloseSocket();
	sockaddr_in GetSocketAddress() const;
protected:
	void SetSocketAddress(const int port, const std::string& ip_address);
	bool IsValidSocket() const;
};
