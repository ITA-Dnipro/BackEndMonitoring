#pragma once

// This class inherits logic work with sockets fom Windows or Linux 
// according to the current OS
#ifdef __linux__	// Linux
#include "CLinuxSocket.h"
class CBaseSocket : public LinuxSocket::CLinuxSocket
{
};

#else				// Windows
#include "CWindowsSocket.h"
class CBaseSocket : public CWindowsSocket
{
};
#endif


