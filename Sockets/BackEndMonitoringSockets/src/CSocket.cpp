#include "stdafx.h"

#include "CSocket.h"

CSocket::CSocket()
	: CBaseSocket(c_invalid_socket)
{ }

CSocket::CSocket(int socket_fd)
	: CBaseSocket(socket_fd)
{ }

bool CSocket::IsValidSocket() const
{
	if (m_socket == c_invalid_socket || m_socket == c_error_socket)
	{
		return false;
	}
	return true;
}

