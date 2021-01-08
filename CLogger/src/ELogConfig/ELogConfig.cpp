#include "stdafx.h"
#include "ELogConfig/ELogConfig.h"

#include <map>

/// <summary>
///		Namespace, that contains all classes and functions
///		to work with CLogger and its macro-functions
/// </summary>
namespace Log
{
	std::string LogConfigToString(const ELogConfig log_config)
	{
		constexpr auto* c_none_str = "";
		constexpr auto* c_log_level_str = "LOG LEVEL";
		constexpr auto* c_log_name_str = "LOG NAME";
		constexpr auto* c_line_number_str = "LINE NUMBER";
		constexpr auto* c_file_name_str = "FILE NAME";
		constexpr auto* c_function_name_str = "FUNCTION NAME";
		constexpr auto* c_thread_id_str = "THREAD ID";
		constexpr auto* c_call_time_str = "CALL TIME";
		constexpr auto* c_message_str = "MESSAGE";
		constexpr auto* c_params_str = "PARAMS";

		const std::map<ELogConfig, std::string> c_string_map
		{
			{ELogConfig::NONE,          c_none_str},
			{ELogConfig::LOG_LEVEL,     c_log_level_str},
			{ELogConfig::LOG_NAME,      c_log_name_str},
			{ELogConfig::LINE_NUMBER,   c_line_number_str},
			{ELogConfig::FILE_NAME,     c_file_name_str},
			{ELogConfig::FUNCTION_NAME, c_function_name_str},
			{ELogConfig::THREAD_ID,     c_thread_id_str},
			{ELogConfig::CALL_TIME,     c_call_time_str},
			{ELogConfig::MESSAGE,       c_message_str},
			{ELogConfig::PARAMS,		c_params_str}
		};

		return c_string_map.at(log_config);
	}
}
