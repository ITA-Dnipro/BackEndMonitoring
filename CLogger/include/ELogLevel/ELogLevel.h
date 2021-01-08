#pragma once
#include "stdafx.h"

enum class CLOGGER_API ELogLevel : unsigned short
{
	NONE, PROD, DEBUG, TRACE
};

CLOGGER_API std::string LogLevelToString(ELogLevel logLevel);