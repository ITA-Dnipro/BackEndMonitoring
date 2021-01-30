#include "stdafx.h"

#ifdef _linux_

#include "CNumericTypesParser.h"
#include "CReadFileWrapper.h"
#include "Utils.h"

#include "PlatformUtils.h"

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

	bool BindSocket(int socket, sockaddress& current_address)
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

	bool Connect(int socket, sockaddress& current_address)
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

bool GetExistingProcessIds(std::vector<unsigned>& container_of_PIDs)
{
	bool success = false;
	std::filesystem::path proc_dir("/proc");
	for (auto& proc : std::filesystem::directory_iterator(proc_dir))
	{
		unsigned PID;
		if (CNumericTypesParser(proc.path().stem().string()).AsUnsignedNumber(PID))
		{
			container_of_PIDs.push_back(PID);
			success = true;
		}
	}
	return success;
}

bool CheckIsProcessActive(unsigned PID)
{
	std::filesystem::path proc_dir("/proc");
	proc_dir /= std::to_string(PID);
	bool success = std::filesystem::exists(proc_dir / "status");
	if (success)
	{
		success = std::filesystem::exists(proc_dir / "stat");
	}
	return success;
}

std::vector<std::string> ParseProcStatFile(const std::string& line)
{
	std::vector<std::string> values = Utils::SplitIntoWords(line, ' ');

	size_t opened_brace_pos = 0;
	for (const auto& value : values)
	{
		size_t opened_brace = value.find("(");
		if (opened_brace != value.npos)
		{
			break;
		}
		++opened_brace_pos;
	}

	size_t closed_brace_pos = 0;
	for (const auto& value : values)
	{
		size_t closed_brace = value.find(")");
		if (closed_brace != value.npos)
		{
			break;
		}
		++closed_brace_pos;
	}

	if (closed_brace_pos != opened_brace_pos)
	{
		for (unsigned i = opened_brace_pos; i <= closed_brace_pos; ++i)
		{
			values[opened_brace_pos].append(" ");
			values[opened_brace_pos].append(values[i]);
			values.erase(values.begin() + i);
		}
	}
	return values;
}

bool GetSysTime(unsigned long long& sys_time)
{
	std::filesystem::path proc_dir("/proc");
	proc_dir /= "stat";
	CReadFileWrapper proc_status(std::move(proc_dir));
	bool success = proc_status.Initialize();
	if (!success)
	{
		return success;
	}

	std::string line;
	if (!(success = proc_status.ReadLine(line)))
	{
		return success;
	}

	auto values = ParseProcStatFile(std::move(line));
	sys_time = 0;
	for (auto& i : values)
	{
		std::string num(i.begin(), i.end());
		unsigned long long val;
		if (CNumericTypesParser(num).AsUnsignedNumber(val))
		{
			sys_time += val;
		}
	}
	return success;
}

bool GetProcessTimes(unsigned PID, unsigned long long& system_time,
	unsigned long long& kernel_time,
	unsigned long long& user_time)
{
	bool success = GetSysTime(system_time);
	if (!success)
	{
		return success;
	}

	std::filesystem::path proc_dir("/proc");
	proc_dir /= std::to_string(PID);
	proc_dir /= "stat";
	CReadFileWrapper proc_status(std::move(proc_dir));
	success = proc_status.Initialize();
	if (!success)
	{
		return success;
	}

	std::string line;
	if (!(success = proc_status.ReadLine(line)))
	{
		return success;
	}

	auto values = Utils::SplitIntoWords(std::move(line), ' ');

	success = CNumericTypesParser(values[13]).AsUnsignedNumber(user_time);
	success = CNumericTypesParser(values[14]).AsUnsignedNumber(kernel_time);

	return success;
}

bool GetPagefileUsage(unsigned PID, unsigned long long& value) {
	std::filesystem::path proc_dir("/proc");
	proc_dir /= std::to_string(PID);
	proc_dir /= "status";
	CReadFileWrapper proc_status(std::move(proc_dir));
	bool success = proc_status.Initialize();
	if (!success) { return success; }

	std::string line;

	while (proc_status.ReadLine(line)) {
		std::string_view line_view(line);
		if (line_view.substr(0, 7) == "VmSize:") {
			size_t from = line.find_first_of("0123456789");
			line.erase(0, from);

			size_t to = line.find_last_of("0123456789");
			line.erase(to + 1, line.npos);

			if ((success = CNumericTypesParser(line).AsUnsignedNumber(value)))
			{
				value *= 1024;
			}
			break;
		}
		success = false;
	}
	return success;
}

bool GetRamUsage(unsigned PID, unsigned long long& value) {
	std::filesystem::path proc_dir("/proc");
	proc_dir /= std::to_string(PID);
	proc_dir /= "status";

	CReadFileWrapper proc_status(std::move(proc_dir));
	bool success = proc_status.Initialize();
	if (!success) { return success; }

	std::string line;

	while (proc_status.ReadLine(line)) {
		if (line.substr(0, 6) == "VmRSS:") {
			size_t from = line.find_first_of("0123456789");
			line.erase(0, from);

			size_t to = line.find_last_of("0123456789");
			line.erase(to + 1, line.npos);

			if ((success = CNumericTypesParser(line).AsUnsignedNumber(value)))
			{
				value *= 1024;
			}
			break;
		}
		success = false;
	}
	return success;
}

bool GetProcessMemoryUsage(unsigned PID, unsigned long long& ram_usage,
	unsigned long long& pagefile_usage)
{
	bool success = GetRamUsage(PID, ram_usage) 
		&& GetPagefileUsage(PID, pagefile_usage);
	return success;
}

#endif