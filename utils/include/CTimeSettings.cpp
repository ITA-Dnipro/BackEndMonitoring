#include "stdafx.h"
#include "CTimeSettings.h"
#include "CLogger/include/Log.h"

CTimeSettings::CTimeSettings(std::shared_ptr<CDataReader> p_data_reader) :
	CSettings(p_data_reader), m_period_time_(30)
{
}

void CTimeSettings::ReadConfigurationFromFile()
{
	CLOG_DEBUG_START_FUNCTION();
	if (nullptr == m_p_data_reader_ || !m_p_data_reader_->IsFileInitialized())
	{
		m_p_data_reader_ ? CLOG_ERROR("Pointer to data reader is empty") :
			CLOG_ERROR("Data reader is not initialized");
		return;
	}

	std::string tmp_string;
	CLOG_TRACE_VAR_CREATION(tmp_string);
	int tmp_int = 0;
	CLOG_TRACE_VAR_CREATION(tmp_int);

	if (m_p_data_reader_->TryToGetStringData("//root/time/Period_time", tmp_string))
		m_period_time_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int) ? tmp_int : m_period_time_;

	CLOG_DEBUG_END_FUNCTION();
}

int CTimeSettings::GetPeriodTime() const
{
	return m_period_time_;
}
