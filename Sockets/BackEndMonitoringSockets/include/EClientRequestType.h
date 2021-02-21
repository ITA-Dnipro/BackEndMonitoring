#pragma once

enum class EClientRequestType
{
	ALL_DATA,
	DISKS_DATA,
	PROCESSES_DATA,
	DATA_RECEIVED,
	LOST_DATA,
	EXIT
};

static const int g_c_requests_num = 6;
static const std::string g_c_requests_types[g_c_requests_num]{ "ALL_DATA", "DISK_DATA",
	"PROCESS_DATA", "DATA RECEIVED" , "LOST DATA", "EXIT" };