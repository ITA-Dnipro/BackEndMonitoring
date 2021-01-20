#include "stdafx.h"

#include "Utils/Utils.h"

namespace LogUtils
{
	std::string AddZero(const int value)
	{
		auto str = std::to_string(value);

		if (value < 10)
		{
			str.insert(str.begin(), '0');
		}

		return str;
	}
	
	std::string GetCurrentTimeString()
	{
		constexpr auto special_year = 1900;
		const auto time             = std::make_unique<tm>();
		auto current_time   = std::chrono::system_clock::to_time_t
			(std::chrono::system_clock::now());

		localtime_s(time.get(), &current_time);

		const auto day   = AddZero(time->tm_mday);
		const auto month = AddZero(time->tm_mon + 1);
		const auto year  = AddZero(time->tm_year + special_year);
		const auto hour  = AddZero(time->tm_hour);
		const auto min   = AddZero(time->tm_min);
		const auto sec   = AddZero(time->tm_sec);

		return day + "." + month + "." + year + " "
			+ hour + ":" + min + ":" + sec;
	}
}
