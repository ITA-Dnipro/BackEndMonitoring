#include "stdafx.h"
#include "CLoggingSettings.h"
#include "CLogger/include/Log.h"

CLoggingSettings::CLoggingSettings(std::shared_ptr<CDataReader> p_data_reader) :
	m_p_data_reader_(p_data_reader), m_log_level_(static_cast<ELogLevel>(1)), 
	m_log_flush_(static_cast<ELogFlush>(1)), m_file_name_("serverlog.txt")
{

}

void CLoggingSettings::ReadConfigurationFromFile()
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

	if (m_p_data_reader_->TryToGetStringData("//root/logging/filename", 
		tmp_string))
		m_file_name_ = tmp_string != "" ? tmp_string : m_file_name_;

	if (m_p_data_reader_->TryToGetStringData("//root/logging/LogLevel", 
		tmp_string))
		m_log_level_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int) ?
		static_cast<ELogLevel>(tmp_int) : m_log_level_;

	if (m_p_data_reader_->TryToGetStringData("//root/logging/flush", 
		tmp_string))
		m_log_flush_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int) ?
		static_cast<ELogFlush>(tmp_int) : m_log_flush_;
	
	CLOG_DEBUG_END_FUNCTION();
}

ELogLevel CLoggingSettings::GetLogLevel() const
{
	return m_log_level_;
}

ELogFlush CLoggingSettings::GetFlush() const
{
	return m_log_flush_;
}

std::string CLoggingSettings::GetFileName() const
{
	return m_file_name_;
}
