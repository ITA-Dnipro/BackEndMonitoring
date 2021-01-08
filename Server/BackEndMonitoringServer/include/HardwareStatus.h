#pragma once

#include "stdafx.h"

class HardwareStatus
{
public:
	// todo: instead of string, need to put other class (like JSONClass)
	HardwareStatus() = delete;
	HardwareStatus(std::chrono::duration<int> pause_duration) :
		period_of_checking_status_(pause_duration)
	{ };
	HardwareStatus(HardwareStatus& const orig) :
		period_of_checking_status_(orig.period_of_checking_status_)
	{ };
	HardwareStatus(HardwareStatus&&) noexcept = delete;
	virtual bool TryFormateDataToSaveFormat(std::string& data_storage) = 0;
	/// <summary>
	/// What threade will be doing. Containe data check logic inside of
	///  infinite loop with timer.
	/// </summary>
	/// <returns></returns>
	virtual void ThreadWorkLogic() = 0;

protected:
	//duration is used as seconds
	std::chrono::duration<int> period_of_checking_status_{};
};

