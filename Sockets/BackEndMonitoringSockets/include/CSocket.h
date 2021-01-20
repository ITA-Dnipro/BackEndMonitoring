#pragma once
#include "PlatformUtils.h"

class CSocket : public CBaseSocket
{
public:
	CSocket(const int port, const std::string& ip_address);
	virtual ~CSocket();
	virtual int GetHandle() const;
	bool CloseSocket();
	sockaddr_in GetSocketAddress() const;
protected:
	int InitSocket();
	void SetSocketAddress(const int port, const std::string& ip_address);
	bool IsValidSocket() const;

	sockaddr_in m_address;
};
