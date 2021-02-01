#pragma once
#include "/home/sasha/BackEndMonitoring/CLogger/include/stdafx.h"

/// <summary>
///		Enumeration that indicates info that logger must print
/// </summary>
enum class CLOGGER_API ELogConfig : unsigned short
{
	NONE, LOG_LEVEL, LOG_NAME, LINE_NUMBER, FILE_NAME,
	FUNCTION_NAME, THREAD_ID, CALL_TIME, MESSAGE,
	PARAMS
};

/// <summary>
///		Casts <c>ELogConfig</c> to <c>std::string</c>
/// </summary>
/// <param name="log_config">
///		<c>ELogConfig</c> to convert
/// </param>
/// <returns>
///		<c>std::string</c> of <c>ELogConfig</c>
/// </returns>
/// <example>
///		ELogConfig config = ELogConfig::LOG_LEVEL;
///		std::string str = LogUtils::LogConfigToString(config);
/// </example>
CLOGGER_API std::string LogConfigToString(ELogConfig log_config);