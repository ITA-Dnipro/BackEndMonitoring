#include "stdafx.h"
#include "PlatformUtils.h"

#ifdef _linux_

CBaseSocket::CBaseSocket()
{
	m_socket = InitSocket();
}

CBaseSocket::~CBaseSocket()
{ 
	PlatformUtils::CloseSocket(m_socket);
}

int CBaseSocket::InitSocket()
{
	return ::socket(AF_INET, SOCK_STREAM, 0);
}


namespace PlatformUtils
{
	bool InitializeWinLibrary()
	{ 
		return true;
	}

	bool FinalizeWinLibrary()
	{ 
		return true;
	}

	bool BindSocket(int socket, sockaddr_in& current_address)
	{
		if (::bind(socket, (struct SOCKADDR*)&current_address,
			sizeof(current_address)) == SUCCESS)
		{
			return true;
		}
		return false;
	}

	bool Listen(int socket)
	{
		if (listen(socket, SOMAXCONN) == SUCCESS)
		{
			return true;
		}
		return false;
	}

	int Accept(int socket)
	{
		return static_cast<int>(accept(socket, 0, 0));
	}

	bool Connect(int socket, sockaddr_in& current_address)
	{
		return connect(socket, (struct sockaddr*)&current_address,
	}

	bool SetUnblockingSocket(int socket)
	{
		int dontblock = 1;
		if (ioctl(socket, FIONBIO, (char*)&dontblock) == SUCCESS)
		{
			return true;
		}
		return false;
	}

	bool CloseSocket(int socket)
	{
		if (socket != SOCKET_INVALID)
		{
			if (close(socket) != ERROR_SOCKET)
			{
				return true;
			}
		}
		return false;
	}
}

#endif