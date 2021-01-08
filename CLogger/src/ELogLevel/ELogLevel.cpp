#include "stdafx.h"
#include "ELogLevel/ELogLevel.h"

#include <map>

std::string LogLevelToString(const ELogLevel log_level)
{
	constexpr auto* c_none_str = "";
	constexpr auto* c_prod_str = "PROD";
	constexpr auto* c_debug_str = "DEBUG";
	constexpr auto* c_trace_str = "TRACE";
	
	const std::map<ELogLevel, std::string> c_string_map
	{
		{ELogLevel::NONE, c_none_str},
		{ELogLevel::PROD, c_prod_str},
		{ELogLevel::DEBUG, c_debug_str},
		{ELogLevel::TRACE, c_trace_str}
	};

	return c_string_map.at(log_level);
}
