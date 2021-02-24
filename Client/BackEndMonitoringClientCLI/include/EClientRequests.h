#pragma once
#include <string>

enum class EClientRequests : size_t
{
	ERR = 0ULL,
	DISKS_DATA,
	PROCESSES_DATA,
	ALL_DATA,
	ALL_DATA_NON_STOP,
	ALL_HISTORY,
	ALL_DATA_CYCLE,
	DATE_MODE,
	CHANGE_OUTPUT_TO_FILE,
	CHANGE_VIEW_MODE,
	EXIT,
	CLS,
	COUNT
};

inline constexpr size_t g_c_exit_request = 8ULL;
static const std::string g_c_client_requests[static_cast<size_t>(EClientRequests::COUNT)]
= { "", "drives data", "processes data", "all data", "non stop", "all stored info",
	"cycle", "date mode", "file", "change view", "exit", "cls" };