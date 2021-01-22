#pragma once

namespace Utils
{
	/// <summary>
	/// Return current date and time in system
	/// </summary>
	/// <returns>format: dd.mm.yyyy hh:mm:ss</returns>
	[[nodiscard]] bool TryGetCurrentDateAndTimeFormatted(std::string&
														 date_time_var_to_save);

	[[nodiscard]] bool TrySetMonthAsNumber(std::string& p_month);

	[[nodiscard]] bool TryGetFormattedDiskName(std::string& name_of_disk);

	[[nodiscard]] bool IsFileEmpty(std::ifstream& file);
	[[nodiscard]] bool IsFileEmpty(std::fstream& file);

	void DisplayError(const std::string& message);
	void DisplayMessage(const std::string& message);
}