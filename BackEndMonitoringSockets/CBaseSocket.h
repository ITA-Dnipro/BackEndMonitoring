#pragma once
#include "stdafx.h"
// This class inherits logic work with sockets fom Windows or Linux 
// according to the current OS
#ifdef __linux__	// Linux
class CBaseSocket : public LinuxSocket::CLinuxSocket
{
protected:
	int m_socket;
};


#else				// Windows
class CBaseSocket
{
public:
	CBaseSocket();
	virtual ~CBaseSocket();

protected:
	bool StartLibrary();
	bool CloseLibrary();

	SOCKET m_socket;
	static bool s_is_started_library;
	static bool s_is_stopped_library;
};

#endif


