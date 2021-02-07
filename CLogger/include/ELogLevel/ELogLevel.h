#pragma once
#include "../include/stdafx.h"

/// <summary>
///		Enumeration indicates level of logging
/// </summary>
enum class CLOGGER_API ELogLevel : unsigned short
{
	NONE_LEVEL, PROD_LEVEL, DEBUG_LEVEL, TRACE_LEVEL
};

/// <summary>
///		Casts <c>ELogLevel</c> to <c>std::string</c>
/// </summary>
/// <param name="log_level">
///		<c>ELogConfig</c> to convert
/// </param>
/// <returns>
///		<c>std::string</c> of <c>ELogLevel</c>
/// </returns>
/// <example>
///		ELogLevel level = ELogLevel::DEBUG_LEVEL;
///		std::string str = LogUtils::LogLevelToString(level);
///	</example>
CLOGGER_API std::string LogLevelToString(ELogLevel log_level);