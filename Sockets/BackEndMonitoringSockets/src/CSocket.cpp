#include "stdafx.h"

#include "CSocket.h"
#include "GlobalVariable.h"
CSocket::CSocket()
	: CBaseSocket(GlobalVariable::c_invalid_socket)
{ }

CSocket::CSocket(int socket_fd)
	: CBaseSocket(socket_fd)
{ }

bool CSocket::IsValidSocket() const
{
	if (m_socket == GlobalVariable::c_invalid_socket 
		|| m_socket == GlobalVariable::c_error_socket)
	{
		return false;
	}
	return true;
}

