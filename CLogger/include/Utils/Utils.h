#pragma once
#include "stdafx.h"

/// <summary>
///		Namespace, that contains all utilities for logger
/// </summary>
namespace LogUtils
{
	/// <summary>
	///		Casts <c>int</c> to <c>std::string</c> with adding
	///		a zero at the start of the string if its need
	/// </summary>
	/// <param name="value">
	///		Value to cast to integer
	/// </param>
	/// <returns>
	///		String, that contains two-digit number
	/// </returns>
	/// <example>
	///		auto number = 123;
	///		std::string twoDigit = AddZero(number);
	/// </example>
	inline std::string AddZero(const int value)
	{
		auto str = std::to_string(value);

		if (value < 10)
		{
			str.insert(str.begin(), '0');
		}

		return str;
	}

	/// <summary>
	///		Gets current system time in <c>std::string</c>
	/// </summary>
	/// <returns>
	///		String, that contains system time
	/// </returns>
	/// <example>
	///		std::string time = GetCurrentTimeString();
	/// </example>
	inline std::string GetCurrentTimeString()
	{
		constexpr auto special_year = 1900;
		const auto time = std::make_unique<tm>();
		auto current_time = std::chrono::system_clock::to_time_t
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
	
	/// <summary>
	///		Gets current thread's id in <c>std::string</c>
	/// </summary>
	/// <returns>
	///		String, that contains thread_id
	/// </returns>
	/// <example>
	///		std::string thisThread = GetThisThreadIdString();
	/// </example>
	inline std::string GetThisThreadIdString()
	{
		std::stringstream ss;
		ss << std::this_thread::get_id();
		return ss.str();
	}

	/// <summary>
	///		Gets filename in <c>std::string</c> by another <c>std::string</c>
	///		that contains path to this file
	/// </summary>
	/// <param name="path">
	///		Path to the file
	/// </param>
	/// <returns>
	///		String, that contains file name
	/// </returns>
	/// <example>
	///		std::string fileName = GetFileNameByPath("file.txt");
	/// </example>
	inline std::string GetFileNameByPath(const std::string& path)
	{ return std::filesystem::path(path).filename().string(); }
}