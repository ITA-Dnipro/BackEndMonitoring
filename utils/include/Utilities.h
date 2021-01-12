#pragma once

#include "stdafx.h"

namespace Utilities
{
	/// <summary>
	/// Return current date and time in system
	/// </summary>
	/// <returns>format: dd.mm.yyyy hh:mm:ss</returns>
	std::string GetCurrentDateAndTimeFormatted();

	namespace HelperDateAndTime
	{
		bool TrySetMonthAsNumber(std::string* p_month);
	}

}