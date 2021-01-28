#include "stdafx.h"
#include "PlatformUtils.h"

#ifdef _WIN64

CBaseSocket::CBaseSocket()
{
	m_socket = InitSocket();
}

CBaseSocket::~CBaseSocket()
{
	PlatformUtils::CloseSocket(static_cast<int>(m_socket));
}

SOCKET CBaseSocket::InitSocket()
{
	return socket(AF_INET, SOCK_STREAM, NULL);
}


namespace PlatformUtils
{
	bool InitializeWinLibrary()
	{
		WSADATA info;
		if(WSAStartup(MAKEWORD(2, 1), &info) == SUCCESS)
		{
			return true;
		}
		return false;
	}

	bool FinalizeWinLibrary()
	{
		if (WSACleanup() == SUCCESS)
		{
			return true;
		}
		return false;
	}

	bool BindSocket(int socket, sockaddress& current_address)
	{
		if (::bind(socket, (SOCKADDR*)&current_address,
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
		return static_cast<int>(accept(socket, NULL, NULL));
	}

	bool Connect(int socket, sockaddress& current_address)
	{
		return connect(socket, (sockaddr*)&current_address,
			sizeof(current_address)) == SUCCESS;
	}

	bool SetUnblockingSocket(int socket)
	{
		u_long iMode = 1UL;
		if (ioctlsocket(socket, FIONBIO, &iMode) == SUCCESS)
		{
			return true;
		}
		return false;
	}

	bool CloseSocket(int socket)
	{
		if (socket != SOCKET_INVALID)
		{
			if (closesocket(socket) != ERROR_SOCKET)
			{
				return true;
			}
		}
		return false;
	}
}
#endif