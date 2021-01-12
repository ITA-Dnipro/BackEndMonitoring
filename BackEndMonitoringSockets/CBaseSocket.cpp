#include "stdafx.h"
#include "CBaseSocket.h"

#ifndef _linux_

bool CBaseSocket::s_is_started_library = false;
bool CBaseSocket::s_is_stopped_library = false;

CBaseSocket::CBaseSocket()
{
	
	if (StartLibrary()) {
		// log pos
	}
	else
	{
		// LOG WSAGetLastError()
	}
}

CBaseSocket::~CBaseSocket()
{
	if (CloseLibrary()) {
		// log pos
	}
	else
	{
		// LOG WSAGetLastError()
	}
}

bool CBaseSocket::StartLibrary()
{
	WSADATA info;
	if (s_is_started_library == false && WSAStartup(MAKEWORD(2, 1), &info) == 0)
	{
		s_is_started_library = true;
		return false;
	}
	return true;
}

bool CBaseSocket::CloseLibrary()
{
	if (s_is_stopped_library == false && WSACleanup)
	{
		s_is_stopped_library = true;
		return false;
	}
	return true;
}

#endif