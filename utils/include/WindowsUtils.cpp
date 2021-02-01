#include "stdafx.h"

#if defined(_WIN64) || defined(_WIN32)

#include "Utils.h"
#include "CLogger/include/Log.h"
#include "PlatformUtils.h"

#pragma warning(disable : 6385)


CBaseSocket::CBaseSocket( )
{
	m_socket = InitSocket( );
}

CBaseSocket::~CBaseSocket( )
{
	PlatformUtils::CloseSocket(static_cast<int>(m_socket));
}

int CBaseSocket::GetSocketFD() const
{
	return static_cast<int>(m_socket);
}

SOCKET CBaseSocket::InitSocket( )
{
	return socket(AF_INET, SOCK_STREAM, NULL);
}


namespace PlatformUtils
{
	bool GetExistingProcessIds(std::vector<unsigned>& container_of_PIDs)
	{
		bool success = false;
		CLOG_DEBUG_START_FUNCTION();
		unsigned short m_max_process_count = 1024;
		CLOG_TRACE_VAR_CREATION(m_max_process_count);
		std::unique_ptr<DWORD> p_process_ids(new DWORD[m_max_process_count]);
		CLOG_TRACE_VAR_CREATION(p_process_ids);
		DWORD cb = m_max_process_count * sizeof(DWORD);
		CLOG_TRACE_VAR_CREATION(cb);
		DWORD bytes_returned = 0;
		CLOG_TRACE_VAR_CREATION(bytes_returned);

		success = (EnumProcesses(p_process_ids.get(), cb, &bytes_returned) != 0);
		CLOG_TRACE_VAR_CREATION(success);

		if (success)
		{
			const int size = bytes_returned / sizeof(DWORD);
			container_of_PIDs.assign(p_process_ids.get(), p_process_ids.get() + size);
		}
		CLOG_DEBUG_END_FUNCTION();
		return success;
	}

	bool CheckIsProcessActive(unsigned PID)
	{
		bool success = false;
		CLOG_DEBUG_START_FUNCTION();
		HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
			FALSE, PID);

		success = (process != 0);
		CLOG_TRACE_VAR_CREATION(success);
		if (success)
		{
			CloseHandle(process);
		}
		CLOG_DEBUG_END_FUNCTION();
		return success;
	}

	bool GetProcessTimes(unsigned PID, unsigned long long& system_time,
						 unsigned long long& kernel_time, 
						 unsigned long long& user_time)
	{
		bool success = false;
		CLOG_DEBUG_START_FUNCTION();
		HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
			FALSE, PID);
		CLOG_TRACE_VAR_CREATION(process);

		success = (process != nullptr);
		CLOG_TRACE_VAR_CREATION(success);

		if (success)
		{
			unsigned processors_count = std::thread::hardware_concurrency();
			CLOG_TRACE_VAR_CREATION(processors_count);

			if (processors_count == 0)
			{
				CloseHandle(process);
				return false;
			}

			FILETIME ftime, fsys, fuser;
			CLOG_TRACE_VAR_CREATION(ftime);
			CLOG_TRACE_VAR_CREATION(fsys);
			CLOG_TRACE_VAR_CREATION(fuser);
			GetSystemTimeAsFileTime(&ftime);
			{
				ULARGE_INTEGER system_time_uli;
				CLOG_TRACE_VAR_CREATION(system_time_uli);
				memcpy(&system_time_uli, &ftime, sizeof(FILETIME));
				system_time = system_time_uli.QuadPart;
			}

			success = (GetProcessTimes(process, &ftime, &ftime, &fsys, &fuser)
				!= 0);
			if (success)
			{
				{
					ULARGE_INTEGER kernel_time_uli;
					CLOG_TRACE_VAR_CREATION(kernel_time_uli);
					memcpy(&kernel_time_uli, &fsys, sizeof(FILETIME));
					kernel_time = kernel_time_uli.QuadPart;
					kernel_time /= processors_count;
				}
				{
					ULARGE_INTEGER user_time_uli;
					CLOG_TRACE_VAR_CREATION(user_time_uli);
					memcpy(&user_time_uli, &fuser, sizeof(FILETIME));
					user_time = user_time_uli.QuadPart;
					user_time /= processors_count;
				}
			}
			CloseHandle(process);
		}
		CLOG_DEBUG_END_FUNCTION();
		return success;
	}

	bool GetProcessMemoryUsage(unsigned PID, unsigned long long& ram_usage,
		unsigned long long& pagefile_usage)
	{
		bool success = false;
		CLOG_DEBUG_START_FUNCTION();
		HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
			FALSE, PID);
		CLOG_TRACE_VAR_CREATION(process);
		success = (process != 0);
		CLOG_TRACE_VAR_CREATION(success);
		if (success)
		{
			PROCESS_MEMORY_COUNTERS pmc;
			CLOG_TRACE_VAR_CREATION(pmc);
			success = (GetProcessMemoryInfo(process, &pmc, sizeof(pmc)) != 0);
			if (success)
			{
				pagefile_usage = pmc.PagefileUsage;
				ram_usage = pmc.WorkingSetSize;
			}
			CloseHandle(process);
		}
		CLOG_DEBUG_END_FUNCTION();
		return success;
	}

	bool TryGetLogicalDisksNames(std::vector<std::string>& all_disks_names)
	{
		CLOG_DEBUG_START_FUNCTION();
		const unsigned short c_size_of_buffer_for_api = 1024U;
		CLOG_TRACE_VAR_CREATION(c_size_of_buffer_for_api);
		//We just skip some chars
		const unsigned short number_of_chars_need_miss = 1U;
		CLOG_TRACE_VAR_CREATION(number_of_chars_need_miss);
		char container_all_disks_names[c_size_of_buffer_for_api +
			c_size_of_buffer_for_api] = {};
		CLOG_TRACE_VAR_CREATION(container_all_disks_names);
		DWORD buffer_size = c_size_of_buffer_for_api;
		CLOG_TRACE_VAR_CREATION(buffer_size);
		DWORD is_created_correct = GetLogicalDriveStrings(buffer_size,
			LPSTR(container_all_disks_names));
		CLOG_TRACE_VAR_CREATION(is_created_correct);
		if (is_created_correct > 0 &&
			is_created_correct <= c_size_of_buffer_for_api)
		{
			char* variable_for_checking_names = container_all_disks_names;
			CLOG_TRACE_VAR_CREATION(variable_for_checking_names);
			while (*variable_for_checking_names)
			{
				std::string name_of_disk = variable_for_checking_names;
				CLOG_TRACE_VAR_CREATION(name_of_disk);
				if (!Utils::TryGetFormattedDiskName(name_of_disk))
				{
					return false;
				}
				
				all_disks_names.emplace_back(name_of_disk);

				//go to the next driver
				variable_for_checking_names +=
					strlen(variable_for_checking_names) +
					number_of_chars_need_miss;
			}

			return true;
		}
		// exception
		CLOG_DEBUG_END_FUNCTION();
		return false;
	}

	bool InitializeWinLibrary( )
	{
		CLOG_DEBUG_START_FUNCTION();
		WSADATA info;
		CLOG_TRACE_VAR_CREATION(info);
		if (WSAStartup(MAKEWORD(2, 1), &info) == SUCCESS)
		{
			return true;
		}
		CLOG_DEBUG_END_FUNCTION();
		return false;
	}

	bool FinalizeWinLibrary( )
	{
		CLOG_DEBUG_START_FUNCTION();
		if (WSACleanup( ) == SUCCESS)
		{
			return true;
		}
		CLOG_DEBUG_END_FUNCTION();
		return false;
	}

	bool BindSocket(int socket, sockaddress& current_address)
	{
		CLOG_DEBUG_START_FUNCTION();
		if (::bind(socket, (SOCKADDR*) &current_address,
			sizeof(current_address)) == SUCCESS)
		{
			return true;
		}
		CLOG_DEBUG_END_FUNCTION();
		return false;
	}

	bool Listen(int socket)
	{
		CLOG_DEBUG_START_FUNCTION();
		if (listen(socket, SOMAXCONN) == SUCCESS)
		{
			return true;
		}
		CLOG_DEBUG_END_FUNCTION();
		return false;
	}

	int Accept(int socket, sockaddress& current_address)
	{
		return static_cast<int>(accept(socket, NULL, NULL));
	}

	bool Connect(int socket, sockaddress& current_address)
	{
		return connect(socket, (sockaddr*) &current_address,
					   sizeof(current_address)) == SUCCESS;
	}

	bool SetUnblockingSocket(int socket)
	{
		CLOG_DEBUG_START_FUNCTION();
		u_long iMode = 1UL;
		CLOG_TRACE_VAR_CREATION(iMode);
		if (ioctlsocket(socket, FIONBIO, &iMode) == SUCCESS)
		{
			return true;
		}
		CLOG_DEBUG_END_FUNCTION();
		return false;
	}

	bool CloseSocket(int socket)
	{
		CLOG_DEBUG_START_FUNCTION();
		if (socket != SOCKET_INVALID)
		{
			if (closesocket(socket) != ERROR_SOCKET)
			{
				return true;
			}
		}
		CLOG_DEBUG_END_FUNCTION();
		return false;
	}

	int GetConnectionError(int socket_fd)
	{
		int error = 0;
		socklen_t size = 0;
		CLOG_DEBUG_START_FUNCTION();
		size = sizeof(error);
		CLOG_TRACE_VAR_CREATION(size);
		CLOG_DEBUG_END_FUNCTION();
		return getsockopt(socket_fd, SOL_SOCKET, SO_ERROR, (char*)&error, 
			&size);
	}
}

#endif