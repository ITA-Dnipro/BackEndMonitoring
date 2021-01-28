#pragma once

typedef struct sockaddr_in sockaddress;

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
	bool TryGetLogicalDisksNames(char* array_to_write,
		const unsigned short c_size_of_buffer_for_api);
	bool InitializeWinLibrary();
	bool FinalizeWinLibrary();

	bool BindSocket(int socket, sockaddress& current_address);
	bool Listen(int socket);
	int Accept(int socket);
	bool Connect(int socket, sockaddress& current_address);
	bool SetUnblockingSocket(int socket);
	bool CloseSocket(int socket);

}

