#pragma once
#include "stdafx.h"

namespace LogUtils {
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
	///		Gets file name by path that stored in <c>std::string</c>
	/// </summary>
	/// <param name="path">
	///		Stores file path
	/// </param>
	/// <returns>
	///		File name
	/// </returns>
	/// <example>
	///		std::string filePath("C:\Users\TestUser\Desktop\TestLogger\file.txt");
	///		std::string fileName = GetFileNameByPath(filePath); // file.txt
	/// </example>
	inline std::string GetFileNameByPath(const std::string& path)
	{
		return std::filesystem::path(path).filename().string();
	}
	
	inline std::string GetTime()
	{
		const auto time = std::make_unique<tm>();
		auto current_time = std::chrono::system_clock::to_time_t
			(std::chrono::system_clock::now());

#ifdef _MSC_VER
		localtime_s(time.get(), &current_time);
#else 
		localtime_r(&current_time, time.get());
#endif

		std::string str;
		str.resize(50u);
		std::strftime(str.data(), str.capacity(), "%d/%m/%Y %X", time.get());
		// Clean redundant \0 symbols, that fills resized string
		str.erase(std::remove(str.begin(), str.end(), '\0'), str.end());

		return str;
	}
}
