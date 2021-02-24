#pragma once

#include <vector>
class CSocket;

#if defined(_WIN64) || defined(_WIN32)

#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include <Windows.h>
using sockaddress = sockaddr_in;

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
using sockaddress = struct sockaddr_in;

#endif

class CBaseSocket
{
public:
	CBaseSocket();
	CBaseSocket(int socket_fd);
	CBaseSocket(sockaddress address, int socket_fd);
	~CBaseSocket() = default;

	[[nodiscard]]int GetSocketFD() const;
	void SetSocket(int socket_fd);
	bool InitSocket();

protected:
#if defined(_WIN64) || defined(_WIN32)

	SOCKET m_socket;
#elif __linux__

	int m_socket;
#endif

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
	bool Listen(int socket, const int connections);
	bool Accept( const int socket_fd, CSocket& client);
	bool Connect(int socket, sockaddress& current_address);
	bool SetUnblockingSocket(int socket);
	bool CloseSocket(int socket);
	void CleanScreen();
}

