#include "stdafx.h"

#include "PlatformUtils.h"

#pragma warning(disable : 6385)

namespace PlatformUtils
{
	bool GetListOfProcessIds(std::list<unsigned>& list_of_PIDs)
	{
		bool success;
		short m_max_process_count = 1024;
		DWORD* p_process_ids = new DWORD[m_max_process_count];
		DWORD cb = m_max_process_count * sizeof(DWORD);
		DWORD bytes_returned = 0;

		success = (EnumProcesses(p_process_ids, cb, &bytes_returned) != 0);
		if (success)
		{
			const int size = bytes_returned / sizeof(DWORD);
			for (int index = 0; index < size; index++)
			{
				list_of_PIDs.push_back(p_process_ids[index]);
			}
		}
		delete[] p_process_ids;

		return success;
	}

	bool CheckIsProcessActive(unsigned PID)
	{
		HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
									 FALSE, PID);

		bool success;
		if (success = (process != 0))
		{
			CloseHandle(process);
		}
		return success;
	}

	bool GetProcessTimes(unsigned PID, unsigned long long& system_time,
						 unsigned long long& kernel_time, 
						 unsigned long long& user_time)
	{
		HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
									 FALSE, PID);

		bool success;
		if (success = (process != 0))
		{
			FILETIME ftime, fsys, fuser;
			GetSystemTimeAsFileTime(&ftime);
			{
				ULARGE_INTEGER system_time_uli;
				memcpy(&system_time_uli, &ftime, sizeof(FILETIME));
				system_time = system_time_uli.QuadPart;
			}

			success = (GetProcessTimes(process, &ftime, &ftime, &fsys, &fuser) 
					   != 0);
			if (success)
			{
				{
					ULARGE_INTEGER kernel_time_uli;
					memcpy(&kernel_time_uli, &fsys, sizeof(FILETIME));
					kernel_time = kernel_time_uli.QuadPart;
				}
				{
					ULARGE_INTEGER user_time_uli;
					memcpy(&user_time_uli, &fuser, sizeof(FILETIME));
					user_time = user_time_uli.QuadPart;
				}
			}
			CloseHandle(process);
		}
		return success;
	}

	bool GetProcessMemoryUsage(unsigned PID, size_t& ram_usage, 
							   size_t& pagefile_usage)
	{
		HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
									 FALSE, PID);
		bool success;
		if (success = (process != 0))
		{
			PROCESS_MEMORY_COUNTERS pmc;
			success = (GetProcessMemoryInfo(process, &pmc, sizeof(pmc)) != 0);
			if (success)
			{
				pagefile_usage = pmc.PagefileUsage;
				ram_usage = pmc.WorkingSetSize;
			}
			CloseHandle(process);
		}
		return success;
	}

	bool TryGetLogicalDisksNames(char* array_to_write, 
		const unsigned short c_size_of_buffer_for_api)
	{
		DWORD buffer_size = c_size_of_buffer_for_api;
		DWORD is_created_correct = GetLogicalDriveStrings(buffer_size,
			LPSTR(array_to_write));
		if (is_created_correct > 0 &&
			is_created_correct <= c_size_of_buffer_for_api)
		{
			return true;
		}

		// exception
		return false;
	}
}