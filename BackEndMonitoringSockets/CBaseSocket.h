#pragma once
#include "stdafx.h"
#include "..\..\CLogger\include\Log.h"
// This class inherits logic work with sockets fom Windows or Linux 
// according to the current OS
#ifdef __linux__	// Linux
class CBaseSocket : public LinuxSocket::CLinuxSocket
{
public:
	CBaseSocket(std::shared_ptr<CLogger> m_logger);
protected:
	std::shared_ptr<CLogger> m_logger;
	int m_socket;
};


#else				// Windows
class CBaseSocket
{
public:
	CBaseSocket(std::shared_ptr<CLogger> logger);
	virtual ~CBaseSocket();

protected:
	bool StartLibrary();
	bool CloseLibrary();

	SOCKET m_socket;
	static bool s_is_started_library;
	static bool s_is_stopped_library;
	std::shared_ptr<CLogger> m_logger;
};

#endif


