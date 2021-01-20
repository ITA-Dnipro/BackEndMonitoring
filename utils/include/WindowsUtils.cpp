#include "stdafx.h"
#include "PlatformUtils.h"

#ifdef _WIN64

bool WindowsLibraryInititializator::s_is_started_library = false;
bool WindowsLibraryInititializator::s_is_stopped_library = false;

void WindowsLibraryInititializator::StartLibrary()
{
	WSADATA info;
	if (s_is_started_library == false && 
		WSAStartup(MAKEWORD(2, 1), &info) == SUCCESS)
	{
		s_is_started_library = true;
	}
}

void WindowsLibraryInititializator::CloseLibrary()
{
	if (s_is_stopped_library == false && WSACleanup() == SUCCESS)
	{
		s_is_stopped_library = true;
		s_is_started_library = false;
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
	bool SetBlockingSocket()
	{
		// TODO add function
		return true;
	}
	bool SetUnblockingSocket()
	{
		// TODO add function
		return true;
	}
}
#endif