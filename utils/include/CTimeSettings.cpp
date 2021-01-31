#include "stdafx.h"
#include "CTimeSettings.h"
#include "CLogger/include/Log.h"

CTimeSettings::CTimeSettings(std::shared_ptr<CDataReader> p_data_reader) :
	p_data_reader_(p_data_reader), period_time_(30)
{
}

void CTimeSettings::ReadConfigurationFromFile()
{
	CLOG_DEBUG_START_FUNCTION();
	if (nullptr == p_data_reader_ || !p_data_reader_->IsFileInitialized())
	{
		p_data_reader_ ? CLOG_ERROR("Pointer to data reader is empty") :
			CLOG_ERROR("Data reader is not initialized");
		return;
	}

	std::string tmp_string;
	int tmp_int = 0;

	if (p_data_reader_->TryToGetStringData("//root/time/Period_time", tmp_string))
		period_time_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int) ? tmp_int : period_time_;

	CLOG_DEBUG_END_FUNCTION();
}

int CTimeSettings::GetPeriodTime() const
{
	return period_time_;
}
