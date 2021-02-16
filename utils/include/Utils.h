#pragma once
#include <vector>
#include <string>

enum class EMemoryConvertType;

namespace Utils
{
	[[nodiscard]] std::vector<std::string> SplitIntoWords(const std::string& str,
		const char delimiter);

	[[nodiscard]] bool TryGetCurrentDateAndTimeFormatted(std::string&
														 date_time_var_to_save);

	[[nodiscard]] bool TrySetMonthAsNumber(std::string& p_month);

	[[nodiscard]] bool TryGetFormattedDiskName(std::string& name_of_disk);

	[[nodiscard]] bool TryCreateFileIfNotExist(const std::string& path_to_file);

	[[nodiscard]] bool IsFileEmpty(std::ifstream& file);
	[[nodiscard]] bool IsFileEmpty(std::fstream& file);
	[[nodiscard]] bool IsFileEmpty(std::ofstream& file);

	#if defined(_WIN64) || defined(_WIN32)
	void DisplayError(const std::string& message);
	#endif
	void DisplayMessage(const std::string& message);
	void DisplayHelp();

	[[nodiscard]] long double ConvertToCountType(
		uintmax_t const value_to_calculate, EMemoryConvertType convert_type);
	[[nodiscard]] long double RoundToDecimal(long double const value_to_round);

	[[nodiscard]] EMemoryConvertType DefineCountType(int count_type_from_xml);

}