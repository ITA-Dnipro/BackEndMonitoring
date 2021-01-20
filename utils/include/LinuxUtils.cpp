#include "stdafx.h"
#include "PlatformUtils.h"

#ifdef _linux_

bool WindowsLibraryInititializator::s_is_started_library = false;
bool WindowsLibraryInititializator::s_is_stopped_library = false;

void WindowsLibraryInititializator::StartLibrary()
{ }

void WindowsLibraryInititializator::CloseLibrary()
{ }

CBaseSocket::CBaseSocket()
{
	m_socket = -1;
}

CBaseSocket::~CBaseSocket()
{ }


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