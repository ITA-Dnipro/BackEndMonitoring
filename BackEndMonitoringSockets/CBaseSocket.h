#pragma once

#ifdef __linux__	// Linux
#include "CLinuxSocket.h"
namespace BaseSocket
{
	class CBaseSocket : public LinuxSocket::CLinuxSocket
	{
	};
}

#else				// Windows
#include "CWindowsSocket.h"
namespace BaseSocket
{
	class CBaseSocket : public WindowsSocket::CWindowsSocket
	{
	};
}
#endif


