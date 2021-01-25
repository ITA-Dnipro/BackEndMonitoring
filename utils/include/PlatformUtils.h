#pragma once

namespace PlatformUtils
{
	bool GetListOfProcessIds(std::list<unsigned>& list_of_PIDs);
	bool CheckIsProcessActive(unsigned PID);
	bool GetProcessTimes(unsigned PID, unsigned long long& system_time,
						 unsigned long long& kernel_time,
						 unsigned long long& user_time);
	bool GetProcessMemoryUsage(unsigned PID, unsigned long long& ram_usage,
		unsigned long long& pagefile_usage);
	bool TryGetLogicalDisksNames(char* array_to_write,
		const unsigned short c_size_of_buffer_for_api);
}