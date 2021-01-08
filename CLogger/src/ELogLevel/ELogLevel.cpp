#include "stdafx.h"
#include "ELogLevel/ELogLevel.h"

static constexpr auto* c_prod_str	= "PROD";
static constexpr auto* c_debug_str	= "DEBUG";
static constexpr auto* c_trace_str	= "TRACE";
static constexpr auto* c_none_str	= "";

std::string LogLevelToString(const ELogLevel logLevel)
{
	switch (logLevel) {
		case ELogLevel::PROD:
		{
			return std::string(c_prod_str);
		}
		case ELogLevel::DEBUG:
		{
			return std::string(c_debug_str);
		}
		case ELogLevel::TRACE:
		{
			return std::string(c_trace_str);
		}
		case ELogLevel::NONE:
		{
			return std::string(c_none_str);
		}
	}

	// TODO: Maybe exception 
	return std::string(c_none_str);
}
