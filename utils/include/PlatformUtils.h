#pragma once

#ifdef _WIN64
	#include <WinSock2.h>
	#include <ws2tcpip.h>
	#pragma comment(lib, "ws2_32.lib")
#elif _linux_
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <stdlib.h>
#endif

class WindowsLibraryInititializator
{
public:
	static void StartLibrary();
	static void CloseLibrary();

private:
	static const int SUCCESS = 0;
	static bool s_is_started_library;
	static bool s_is_stopped_library;
};

class CBaseSocket
{
public:
	CBaseSocket();
	~CBaseSocket();

protected:
#ifdef _WIN64
	SOCKET m_socket;
#elif _linux_
	int m_socket;
#endif

};

namespace PlatformUtils
{
	bool SetBlockingSocket();
	bool SetUnblockingSocket();

}

