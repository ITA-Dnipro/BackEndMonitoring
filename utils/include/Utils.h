#pragma once
#include <vector>
#include <string>
#include <filesystem>

enum class EMemoryConvertType;

namespace Utils
{
	/// <summary>
	/// Return current date and time in system
	/// </summary>
	/// <returns>format: dd.mm.yyyy hh:mm:ss</returns>

	[[nodiscard]] std::vector<std::string> SplitIntoWords(const std::string& str,
		const char delimiter);

	[[nodiscard]] bool TryGetCurrentDateAndTimeFormatted(std::string&
														 date_time_var_to_save, const std::string& format = "%d.%m.%Y %X");

	[[nodiscard]] bool TrySetMonthAsNumber(std::string& p_month);

	[[nodiscard]] bool TryGetFormattedDiskName(std::string& name_of_disk);

	[[nodiscard]] bool TryCreateFileIfNotExist(const std::filesystem::path& path_to_file);

	[[nodiscard]] bool IsFileEmpty(std::ifstream& file);
	[[nodiscard]] bool IsFileEmpty(std::fstream& file);
	[[nodiscard]] bool IsFileEmpty(std::ofstream& file);

	[[nodiscard]] long double ConvertToCountType(
		uintmax_t const value_to_calculate, EMemoryConvertType convert_type);
	[[nodiscard]] long double RoundToDecimal(long double const value_to_round);

	[[nodiscard]] EMemoryConvertType DefineCountType(int count_type_from_xml);

	bool StringToDate(const std::string& date_str, const std::string& date_format,
					          time_t& result);

	[[nodiscard]] bool TryCreateDirectory(const std::string& path,
		std::filesystem::perms permission = std::filesystem::perms::all,
		std::filesystem::perm_options perms_action =
		std::filesystem::perm_options::replace);

	[[nodiscard]] bool IsDayPassed(std::string& day);
	[[nodiscard]] bool IsHourPassed(std::string& time);
	[[nodiscard]] char DetermineSectDividingSymbol(const std::string& path);
	bool TimeToString(time_t time, std::string& to_str,
		              const std::string& format);

#if defined(_WIN64) || defined(_WIN32)

	void DisplayError(const std::string& message);

    bool GetModulePath(CString& module_path);
    bool EscapePath(CString& path);

#endif

	void DisplayMessage(const std::string& message);
	void DisplayHelp();

	std::string GetRelativePath();
}
