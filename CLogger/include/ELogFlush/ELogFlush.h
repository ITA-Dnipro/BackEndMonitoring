#pragma once
#include "../include/stdafx.h"

/// <summary>
///		Enumeration that indicates if logger must flushes the stream
/// </summary>
enum class CLOGGER_API ELogFlush : unsigned short
{
	NONE, FLUSH, NOT_FLUSH
};

/// <summary>
///		Casts <c>ELogFlush</c> to <c>std::string</c>
/// </summary>
/// <param name="log_flush">
///		<c>ELogConfig</c> to convert
/// </param>
/// <returns>
///		<c>std::string</c> of <c>ELogFlush</c>
/// </returns>
/// <example>
///		ELogFlush flush = ELogFlush::FLUSH;
///		std::string str = LogUtils::LogFlushToString(flush);
/// </example>
CLOGGER_API std::string LogFlushToString(ELogFlush log_flush);