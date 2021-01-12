#include "stdafx.h"
#include "ELogLevel/ELogLevel.h"

#include <map>

/// <summary>
///		Namespace, that contains all classes and functions
///		to work with CLogger and its macro-functions
/// </summary>
namespace Log
{
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
	///		ELogLevel level = ELogLevel::DEBUG;
	///		std::string str = Log::LogLevelToString(level);
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
}
