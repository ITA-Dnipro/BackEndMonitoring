#pragma once

namespace Utils
{
	/// <summary>
	/// Return current date and time in system
	/// </summary>
	/// <returns>format: dd.mm.yyyy hh:mm:ss</returns>
	bool TryGetCurrentDateAndTimeFormatted(std::string& 
		date_time_var_to_save);

	bool TrySetMonthAsNumber(std::string& p_month);
	
	bool TryGetFormattedDiskName(std::string& name_of_disk);
}
