#pragma once
#include "PlatformUtils.h"

class CSocket : public CBaseSocket
{
public:
	CSocket() = delete;
	explicit CSocket(const int port, const std::string& ip_address);
	CSocket(const CSocket&) = delete;
	CSocket(CSocket&&) noexcept = delete;
	~CSocket() noexcept = default;

	bool CloseSocket();
	[[nodiscard]]  sockaddress GetSocketAddress() const;

protected:
	void SetSocketAddress(const int port, const std::string& ip_address);
	bool IsValidSocket() const;
	
};
