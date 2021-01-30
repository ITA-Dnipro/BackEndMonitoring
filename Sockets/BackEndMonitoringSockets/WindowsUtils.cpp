#include "stdafx.h"
#include ""

#ifdef _WIN64

#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

bool WindowsLibraryInititializator::s_is_started_library = false;
bool WindowsLibraryInititializator::s_is_stopped_library = false;

void WindowsLibraryInititializator::StartLibrary()
{
	WSADATA info;
	if (s_is_started_library == false && WSAStartup(MAKEWORD(2, 1), &info) == 0)
	{
		s_is_started_library = true;
	}
}

void WindowsLibraryInititializator::CloseLibrary()
{
	if (s_is_stopped_library == false && WSACleanup)
	{
		s_is_stopped_library = true;
	}
}

CBaseSocket::CBaseSocket()
{
	m_socket = SOCKET_ERROR;
	WindowsLibraryInititializator::StartLibrary();
}

CBaseSocket::~CBaseSocket()
{
	WindowsLibraryInititializator::CloseLibrary();
}

namespace PlatformUtils
{

}


#endif // _WIN64
