#pragma once
#include "stdafx.h"

/// <summary>
///		Namespace, that contains all utilities for logger
/// </summary>
namespace LogUtils
{
	CLOGGER_API std::string GetCurrentTimeString();
	
	/// <summary>
	///		Gets current thread's id in <c>std::string</c>
	/// </summary>
	/// <returns>
	///		String, that contains thread_id
	/// </returns>
	/// <example>
	///		std::string thisThread = ThisThreadGetIdString();
	/// </example>
	inline std::string ThisThreadGetIdString()
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