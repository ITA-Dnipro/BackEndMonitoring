#include "CWindowsSocket.h"

WindowsSocket::CWindowsSocket::CWindowsSocket()
{
	if (StartLibrary()) {
		// log pos
	}
	else
	{
		// LOG WSAGetLastError()
	}
}

WindowsSocket::CWindowsSocket::~CWindowsSocket()
{
	if (CloseLibrary()) {
		// log pos
	}
	else
	{
		// LOG WSAGetLastError()
	}
}

bool WindowsSocket::CWindowsSocket::StartLibrary()
{
	WSADATA info;
	if (WSAStartup(MAKEWORD(2, 0), &info) == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}

bool WindowsSocket::CWindowsSocket::CloseLibrary()
{
	if (WSACleanup)
	{
		return false;
	}
	return true;
}
