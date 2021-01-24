#pragma once
#include "stdafx.h"

/// <summary>
///		Namespace, that contains all utilities for logger
/// </summary>
namespace LogUtils
{
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
		const auto time = std::make_unique<tm>();
		auto current_time = std::chrono::system_clock::to_time_t
			(std::chrono::system_clock::now());

		localtime_s(time.get(), &current_time);

		std::string str;
		str.resize(50u);
		std::strftime(str.data(), str.capacity(), "%c", time.get());
		return str;
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