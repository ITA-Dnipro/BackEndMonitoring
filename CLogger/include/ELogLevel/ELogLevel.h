#pragma once
#include "stdafx.h"

/// <summary>
///		Namespace, that contains all classes and functions
///		to work with CLogger and its macro-functions
/// </summary>
namespace Log
{
	enum class CLOGGER_API ELogLevel : unsigned short
	{
		NONE, PROD, DEBUG, TRACE
	};

	CLOGGER_API std::string LogLevelToString(ELogLevel log_level);
}