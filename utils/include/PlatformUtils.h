#pragma once

#include <vector>

#if defined(_WIN64) || defined(_WIN32)

#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include <Windows.h>
#elif __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>

#endif

using sockaddress = sockaddr_in;

constexpr int ERROR_SOCKET = -1;
constexpr int SOCKET_INVALID = 0;
constexpr int SUCCESS = 0;

class CBaseSocket
{
public:
	CBaseSocket();
	~CBaseSocket();

	int GetSocketFD() const;

protected:
#if defined(_WIN64) || defined(_WIN32)
	SOCKET InitSocket();

	SOCKET m_socket;
#elif __linux__
	int InitSocket();

	int m_socket;
#endif

	sockaddress m_address;
};

namespace PlatformUtils
{
	bool GetExistingProcessIds(std::vector<unsigned>& container_of_PIDs);
	bool CheckIsProcessActive(unsigned PID);
	bool GetProcessTimes(unsigned PID, unsigned long long& system_time,
						 unsigned long long& kernel_time,
						 unsigned long long& user_time);
	bool GetProcessMemoryUsage(unsigned PID, unsigned long long& ram_usage,
		unsigned long long& pagefile_usage);
	bool TryGetLogicalDisksNames(std::vector<std::string>& all_disks_names);
	bool InitializeWinLibrary();
	bool FinalizeWinLibrary();

	bool BindSocket(int socket, sockaddress& current_address);
	bool Listen(int socket);
	int Accept(int socket, sockaddress& current_address);
	bool Connect(int socket, sockaddress& current_address);
	bool SetUnblockingSocket(int socket);
	bool CloseSocket(int socket);
	int GetConnectionError(int socket_fd);

}

