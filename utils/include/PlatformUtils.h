#pragma once

#ifdef _WIN64
	#include <WinSock2.h>
	#include <ws2tcpip.h>
	#pragma comment(lib, "ws2_32.lib")
#elif _linux_
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <arpa/inet.h>
#endif

constexpr int ERROR_SOCKET = -1;
constexpr int SOCKET_INVALID = 0;
constexpr int SUCCESS = 0;

class CBaseSocket
{
public:
	CBaseSocket();
	~CBaseSocket();

protected:
#ifdef _WIN64
	SOCKET InitSocket();

	SOCKET m_socket;
#elif _linux_
	int InitSocket();

	int m_socket;
#endif

	sockaddr_in m_address;
};

namespace PlatformUtils
{
	bool InitializeWinLibrary();
	bool FinalizeWinLibrary();

	bool BindSocket(int socket, sockaddr_in& current_address);
	bool Listen(int socket);
	int Accept(int socket);
	bool Connect(int socket, sockaddr_in& current_address);
	bool SetUnblockingSocket(int socket);
	bool CloseSocket(int socket);

}

