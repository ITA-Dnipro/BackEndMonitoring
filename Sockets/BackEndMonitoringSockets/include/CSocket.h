#pragma once
#include "PlatformUtils.h"

class CSocket : public CBaseSocket
{
public:
	CSocket(const int port, const std::string& ip_address);
	virtual int GetSocketFD() const;
	bool CloseSocket();
	sockaddress GetSocketAddress() const;
protected:
	void SetSocketAddress(const int port, const std::string& ip_address);
	bool IsValidSocket() const;
};
