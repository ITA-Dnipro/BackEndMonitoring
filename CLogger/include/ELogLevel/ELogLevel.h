#pragma once
#include "stdafx.h"


enum class CLOGGER_API ELogLevel : unsigned short
{
	NONE_LEVEL, PROD_LEVEL, DEBUG_LEVEL, TRACE_LEVEL
};

CLOGGER_API std::string LogLevelToString(ELogLevel log_level);