#include "stdafx.h"

#include "CSocket.h"

#if defined(_WIN64) || defined(_WIN32)
#include "GlobalVariable.h"
#include "Utils.h"
#include "Log.h"
#include "PlatformUtils.h"

#pragma warning(disable : 6385)


CBaseSocket::CBaseSocket( ) : m_socket(GlobalVariable::c_invalid_socket)
{ }

CBaseSocket::CBaseSocket(int socket_fd) : m_socket(socket_fd)
{ }

int CBaseSocket::GetSocketFD() const
{
	return static_cast<int>(m_socket);
}

void CBaseSocket::SetSocket(int socket_fd)
{
	if(socket_fd > 0 && socket_fd <= GlobalVariable::c_max_valid_socket)
	{
		m_socket = socket_fd;
	}
}

bool CBaseSocket::InitSocket( )
{
	m_socket = socket(AF_INET, SOCK_STREAM, NULL);
	if(m_socket != GlobalVariable::c_error_socket)
	{
		return true;
	}
	return false;
}


namespace PlatformUtils
{
	bool GetExistingProcessIds(std::vector<unsigned>& container_of_PIDs)
	{
		bool success = false;
		CLOG_TRACE_START_FUNCTION();
		CLOG_TRACE_VAR_CREATION(success);

		unsigned short m_max_process_count = 1024;
		CLOG_TRACE_VAR_CREATION(m_max_process_count);
		std::unique_ptr<DWORD> p_process_ids(new DWORD[m_max_process_count]);
		CLOG_TRACE_VAR_CREATION(p_process_ids);
		DWORD cb = m_max_process_count * sizeof(DWORD);
		CLOG_TRACE_VAR_CREATION(cb);
		DWORD bytes_returned = 0;
		CLOG_TRACE_VAR_CREATION(bytes_returned);

		success = (EnumProcesses(p_process_ids.get(), cb, &bytes_returned) != 0);

		if (success)
		{
			const int size = bytes_returned / sizeof(DWORD);
			CLOG_TRACE_VAR_CREATION(size);
			container_of_PIDs.assign(p_process_ids.get(), p_process_ids.get() + size);
			CLOG_TRACE("PID's enumerated successfiully");
		}
		else
		{ CLOG_TRACE("Can't enumerate PID's.");}

		CLOG_TRACE_END_FUNCTION_WITH_RETURN(success);
		return success;
	}

	bool CheckIsProcessActive(unsigned PID)
	{
		bool success = false;
		CLOG_TRACE_START_FUNCTION();
		CLOG_TRACE_VAR_CREATION(success);

		HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
			FALSE, PID);

		success = (process != 0);
		if (success)
		{
			CloseHandle(process);
		}
		CLOG_TRACE_END_FUNCTION_WITH_RETURN(success);
		return success;
	}

	bool GetProcessTimes(unsigned PID, unsigned long long& system_time,
						 unsigned long long& kernel_time,
						 unsigned long long& user_time)
	{
		bool success = false;
		CLOG_TRACE_START_FUNCTION();
		CLOG_TRACE_VAR_CREATION(success);

		HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
			FALSE, PID);
		CLOG_TRACE_VAR_CREATION(process);

		success = (process != nullptr);
		if (success)
		{
			unsigned processors_count = std::thread::hardware_concurrency();
			CLOG_TRACE_VAR_CREATION(processors_count);

			if (processors_count == 0)
			{
				CloseHandle(process);
				CLOG_ERROR("Can't get count of logical CPU's.");
				return false;
			}

			FILETIME ftime, fsys, fuser;
			CLOG_TRACE_VAR_CREATION(ftime);
			CLOG_TRACE_VAR_CREATION(fsys);
			CLOG_TRACE_VAR_CREATION(fuser);

			ULARGE_INTEGER temp_uli;
			CLOG_TRACE_VAR_CREATION(temp_uli);

			GetSystemTimeAsFileTime(&ftime);
			memcpy(&temp_uli, &ftime, sizeof(FILETIME));
			system_time = temp_uli.QuadPart;

			success = (GetProcessTimes(process, &ftime, &ftime, &fsys, &fuser)
				!= 0);
			if (success)
			{
				memcpy(&temp_uli, &fsys, sizeof(FILETIME));
				kernel_time = temp_uli.QuadPart;
				kernel_time /= processors_count;

				memcpy(&temp_uli, &fuser, sizeof(FILETIME));
				user_time = temp_uli.QuadPart;
				user_time /= processors_count;
			}
			else
			{ CLOG_WARNING("Can't fet processor times for process.");}

			CloseHandle(process);
		}
		else
		{ CLOG_TRACE_WITH_PARAMS("Can't open HANDLE for process ", PID);}

		CLOG_TRACE_END_FUNCTION_WITH_RETURN(success);
		return success;
	}

	bool GetProcessMemoryUsage(unsigned PID, unsigned long long& ram_usage,
		unsigned long long& pagefile_usage)
	{
		bool success = false;
		CLOG_TRACE_START_FUNCTION();
		CLOG_TRACE_VAR_CREATION(success);

		HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
			FALSE, PID);
		CLOG_TRACE_VAR_CREATION(process);
		success = (process != 0);
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
		else
		{ CLOG_TRACE_WITH_PARAMS("Can't open HANDLE for process ", PID);}

		CLOG_TRACE_END_FUNCTION_WITH_RETURN(success);
		return success;
	}

	bool TryGetLogicalDisksNames(std::vector<std::string>& all_disks_names)
	{
		CLOG_TRACE_START_FUNCTION();
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
		CLOG_TRACE_END_FUNCTION();
		return false;
	}

	bool InitializeWinLibrary( )
	{
		CLOG_DEBUG_START_FUNCTION();
		WSADATA info;
		CLOG_TRACE_VAR_CREATION(info);
		if (WSAStartup(MAKEWORD(2, 1), &info) == GlobalVariable::c_success)
		{
			return true;
		}
		CLOG_DEBUG_END_FUNCTION();
		return false;
	}

	bool FinalizeWinLibrary( )
	{
		if (WSACleanup( ) == GlobalVariable::c_success)
		{
			return true;
		}
		return false;
	}

	bool BindSocket(int socket, sockaddress& current_address)
	{
		CLOG_DEBUG_START_FUNCTION();
		if (::bind(socket, (SOCKADDR*) &current_address,
			sizeof(current_address)) == GlobalVariable::c_success)
		{
			return true;
		}
		CLOG_DEBUG_END_FUNCTION();
		return false;
	}

	bool Listen(int socket, const int connections)
	{
		CLOG_DEBUG_START_FUNCTION();
		if (listen(socket, connections) == GlobalVariable::c_success)
		{
			return true;
		}
		CLOG_DEBUG_END_FUNCTION();
		return false;
	}

	bool Accept(const int socket_fd, CSocket& client)
	{
		int accepted_socket = static_cast<int>(accept(socket_fd, NULL, NULL));
		if(accepted_socket < 0)
		{
			return false;
		}
		client.SetSocket(accepted_socket);
		return true;
	}

	bool Connect(int socket, sockaddress& current_address)
	{
		return connect(socket, (sockaddr*) &current_address,
					   sizeof(current_address)) == GlobalVariable::c_success;
	}

	bool SetUnblockingSocket(int socket)
	{
		CLOG_DEBUG_START_FUNCTION();
		u_long iMode = 1UL;
		CLOG_TRACE_VAR_CREATION(iMode);
		if (ioctlsocket(socket, FIONBIO, &iMode) == GlobalVariable::c_success)
		{
			return true;
		}
		CLOG_DEBUG_END_FUNCTION();
		return false;
	}

	bool CloseSocket(int socket)
	{
		CLOG_DEBUG_WITH_PARAMS("Close socket", socket);
		if (socket != GlobalVariable::c_invalid_socket)
		{
			if (closesocket(socket) != GlobalVariable::c_error_socket)
			{
				return true;
			}
		}
		return false;
	}

	void CleanScreen()
	{
		system("cls");
	}
}

#endif
