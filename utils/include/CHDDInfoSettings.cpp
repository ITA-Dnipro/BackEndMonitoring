#include "stdafx.h"
#include "CHDDInfoSettings.h"
#include "CLogger/include/Log.h"

CHDDInfoSettings::CHDDInfoSettings(std::shared_ptr<CDataReader> p_data_reader) :
	CSettings(p_data_reader), m_file_name_("hddinfo.txt"), m_check_hdd_(true),
	m_count_type_(0), m_period_time_(30)
{

}

void CHDDInfoSettings::ReadConfigurationFromFile()
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
	bool tmp_bool = false;
	CLOG_TRACE_VAR_CREATION(tmp_bool);

	if (m_p_data_reader_->TryToGetStringData("//root/Server/servername", 
		tmp_string))
		m_file_name_ = tmp_string != "" ? tmp_string : m_file_name_;

	if (m_p_data_reader_->TryToGetStringData("//root/Server/serverdisplayname",
		tmp_string))
		m_check_hdd_ = CDataReader::TryToConvertToBool(tmp_string, tmp_bool) ? 
		tmp_bool : m_check_hdd_;

	if (m_p_data_reader_->TryToGetStringData("//root/Server/listenerport", 
		tmp_string))
		m_count_type_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int)
		? tmp_int : m_count_type_;

	if (m_p_data_reader_->TryToGetStringData("//root/time/Period_time", tmp_string))
		m_period_time_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int) ? tmp_int : m_period_time_;

	CLOG_DEBUG_END_FUNCTION();
}

std::string CHDDInfoSettings::GetFileName() const
{
	return m_file_name_;
}

bool CHDDInfoSettings::GetCheckHdd() const
{
	return m_check_hdd_;
}

int CHDDInfoSettings::GetCountType() const
{
	return m_count_type_;
}

int CHDDInfoSettings::GetPeriodTime() const
{
	return m_period_time_;
}
