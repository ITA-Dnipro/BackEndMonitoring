#include "stdafx.h"
#include "CBaseSocket.h"

#ifdef _WIN64

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
	if (s_is_started_library == false && WSAStartup(MAKEWORD(2, 0), &info) == SOCKET_ERROR)
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