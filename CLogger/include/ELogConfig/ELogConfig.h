#pragma once
#include "stdafx.h"

enum class CLOGGER_API ELogConfig : unsigned short
{
	NONE, LOG_LEVEL, LOG_NAME, LINE_NUMBER, FILE_NAME,
	FUNCTION_NAME, THREAD_ID, CALL_TIME, MESSAGE,
	PARAMS
};

CLOGGER_API std::string LogConfigToString(ELogConfig log_config);