#include "stdafx.h"

CWindowsSocket::CWindowsSocket()
{
	if (StartLibrary()) {
		// log pos
	}
	else
	{
		// LOG WSAGetLastError()
	}
}

CWindowsSocket::~CWindowsSocket()
{
	if (CloseLibrary()) {
		// log pos
	}
	else
	{
		// LOG WSAGetLastError()
	}
}

bool CWindowsSocket::StartLibrary()
{
	WSADATA info;
	if (WSAStartup(MAKEWORD(2, 0), &info) == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}

bool CWindowsSocket::CloseLibrary()
{
	if (WSACleanup)
	{
		return false;
	}
	return true;
}
