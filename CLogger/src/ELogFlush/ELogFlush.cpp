#include "stdafx.h"

#include "ELogFlush/ELogFlush.h"

std::string LogFlushToString(const ELogFlush log_flush)
{
	constexpr auto* c_none_str = "";
	constexpr auto* c_flush_str = "FLUSH";
	constexpr auto* c_not_flush_str = "NOT FLUSH";

	const std::map<ELogFlush, std::string> c_string_map
	{
		{ELogFlush::NONE, c_none_str},
		{ELogFlush::FLUSH, c_flush_str},
		{ELogFlush::NOT_FLUSH, c_not_flush_str}
	};

	return c_string_map.at(log_flush);
}
