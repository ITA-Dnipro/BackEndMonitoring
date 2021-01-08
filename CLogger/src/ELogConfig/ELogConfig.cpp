#include "stdafx.h"

#include "ELogConfig/ELogConfig.h"

static constexpr auto* c_log_level_str = "LOG LEVEL";
static constexpr auto* c_line_number_str = "LINE NUMBER";
static constexpr auto* c_file_name_str = "FILE NAME";
static constexpr auto* c_function_name_str = "FUNCTION NAME";
static constexpr auto* c_thread_id_str = "THREAD ID";
static constexpr auto* c_call_time_str = "CALL TIME";
static constexpr auto* c_message_str = "MESSAGE";
static constexpr auto* c_log_name_str = "LOG NAME";
static constexpr auto* c_params_str = "PARAMS";
static constexpr auto* c_none_str = "";

std::string LogConfigToString(const ELogConfig logConfig)
{
	switch (logConfig)
	{
	case ELogConfig::LOG_LEVEL:
	{
		return std::string(c_log_level_str);
	}
	case ELogConfig::LINE_NUMBER:
	{
		return std::string(c_line_number_str);
	}
	case ELogConfig::FILE_NAME:
	{
		return std::string(c_file_name_str);
	}
	case ELogConfig::FUNCTION_NAME:
	{
		return std::string(c_function_name_str);
	}
	case ELogConfig::THREAD_ID:
	{
		return std::string(c_thread_id_str);
	}
	case ELogConfig::CALL_TIME:
	{
		return std::string(c_call_time_str);
	}
	case ELogConfig::MESSAGE:
	{
		return std::string(c_message_str);
	}
	case ELogConfig::LOG_NAME:
	{
		return std::string(c_log_name_str);
	}
	case ELogConfig::PARAMS:
	{
		return std::string(c_params_str);
	}
	case ELogConfig::NONE:
	{
		return std::string(c_none_str);
	}
	}

	// TODO: Maybe exception 
	return std::string(c_none_str);
}
