#pragma once

namespace Utils
{
	/// <summary>
	/// Return current date and time in system
	/// </summary>
	/// <returns>format: dd.mm.yyyy hh:mm:ss</returns>
	bool GetCurrentDateAndTimeFormatted(std::string& 
		date_time_var_to_save);

	bool TrySetMonthAsNumber(std::string& p_month);

	void DisplayError(const std::string& message);
	void DisplayMessage(const std::string& message);

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
	{ return std::filesystem::path(path).filename().string(); }
}