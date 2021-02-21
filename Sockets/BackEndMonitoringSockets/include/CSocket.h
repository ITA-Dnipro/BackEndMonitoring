#pragma once
#include "PlatformUtils.h"

class CSocket : public CBaseSocket
{
public:
	explicit CSocket();
	explicit CSocket(int socket_fd);
	CSocket(const CSocket& obj) = default;
	CSocket(CSocket&& obj) noexcept = default;
	CSocket& operator = (const CSocket& obj) = default;

	bool IsValidSocket() const;

};
