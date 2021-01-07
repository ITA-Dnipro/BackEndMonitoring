#pragma once

#include <string>
#include <chrono>

class HardwareStatus
{
public:
	// todo: instead of string, need to put other class (like JSONClass)
	virtual bool FormateDataToSaveFromat(std::string& data_storage) = 0;

	/// <summary>
	/// What threade will be doing. Containe data check logic inside of
	///  infinite loop with timer.
	/// </summary>
	/// <returns>false if received stop-event</returns>
	virtual bool ThreadWorkLogic() = 0;

protected:
	//duration is used as seconds
	std::chrono::duration<int> period_of_checking_status;
};

