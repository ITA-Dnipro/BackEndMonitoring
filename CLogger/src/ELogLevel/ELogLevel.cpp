#include "CLogger/include/stdafx.h"

#include "ELogLevel/ELogLevel.h"

std::string LogLevelToString(const ELogLevel log_level)
{
	constexpr auto* c_none_str  = "";
	constexpr auto* c_prod_str  = "PROD";
	constexpr auto* c_debug_str = "DEBUG";
	constexpr auto* c_trace_str = "TRACE";

	const std::map<ELogLevel, std::string> c_string_map
	{
		{ELogLevel::NONE_LEVEL, c_none_str},
		{ELogLevel::PROD_LEVEL, c_prod_str},
		{ELogLevel::DEBUG_LEVEL, c_debug_str},
		{ELogLevel::TRACE_LEVEL, c_trace_str}
	};

	return c_string_map.at(log_level);
}
