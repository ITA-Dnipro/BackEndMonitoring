#include "stdafx.h"
#include "CProcessesInfoSettings.h"
#include "CLogger/include/Log.h"

CProcessesInfoSettings::CProcessesInfoSettings(std::shared_ptr<CDataReader> p_data_reader) :
	CSettings(p_data_reader), m_file_name_("processesinfo.txt"), m_check_processes_(true),
	m_count_type_(0), m_period_time_(30)
{

}

void CProcessesInfoSettings::ReadConfigurationFromFile()
{
	CLOG_DEBUG_START_FUNCTION();
	if (nullptr == m_p_data_reader_ || !m_p_data_reader_->IsFileInitialized())
	{
		m_p_data_reader_ ? CLOG_ERROR("Pointer to data reader is empty") :
			CLOG_ERROR("Data reader is not initialized");
		return;
	}

	std::string tmp_string;
	int tmp_int = 0;
	bool tmp_bool = false;

	if (m_p_data_reader_->TryToGetStringData("//root/processesinfo/filename", tmp_string))
		m_file_name_ = tmp_string != "" ? tmp_string : m_file_name_;

	if (m_p_data_reader_->TryToGetStringData("//root/processesinfo/checkprocesses", tmp_string))
		m_check_processes_ = CDataReader::TryToConvertToBool(tmp_string, tmp_bool) ? tmp_bool : m_check_processes_;

	if (m_p_data_reader_->TryToGetStringData("//root/processesinfo/counttype", tmp_string))
		m_count_type_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int) ? tmp_int : m_count_type_;

	if (m_p_data_reader_->TryToGetStringData("//root/time/Period_time", tmp_string))
		m_period_time_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int) ? tmp_int : m_period_time_;

	CLOG_DEBUG_END_FUNCTION();
}

std::string CProcessesInfoSettings::GetFileName() const
{
	return m_file_name_;
}

bool CProcessesInfoSettings::GetCheckProcesses() const
{
	return m_check_processes_;
}

int CProcessesInfoSettings::GetCountType() const
{
	return m_count_type_;
}

int CProcessesInfoSettings::GetPeriodTime() const
{
	return m_period_time_;
}
