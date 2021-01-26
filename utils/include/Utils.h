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
}