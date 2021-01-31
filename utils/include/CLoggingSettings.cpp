#include "stdafx.h"
#include "CLoggingSettings.h"
#include "CLogger/include/Log.h"

CLoggingSettings::CLoggingSettings(std::shared_ptr<CDataReader> p_data_reader) :
	p_data_reader_(p_data_reader), log_level_(static_cast<ELogLevel>(1)), 
	log_flush_(static_cast<ELogFlush>(1)), file_name_("serverlog.txt")
{

}

void CLoggingSettings::ReadConfigurationFromFile()
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
	bool tmp_bool = false;

	if (p_data_reader_->TryToGetStringData("//root/logging/filename", tmp_string))
		file_name_ = tmp_string != "" ? tmp_string : file_name_;

	if (p_data_reader_->TryToGetStringData("//root/logging/LogLevel", tmp_string))
		log_level_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int) ? static_cast<ELogLevel>(tmp_int) : log_level_;

	if (p_data_reader_->TryToGetStringData("//root/logging/flush", tmp_string))
		log_flush_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int) ? static_cast<ELogFlush>(tmp_int) : log_flush_;
	
	CLOG_DEBUG_END_FUNCTION();
}

ELogLevel CLoggingSettings::GetLogLevel() const
{
	return log_level_;
}

ELogFlush CLoggingSettings::GetFlush() const
{
	return log_flush_;
}

std::string CLoggingSettings::GetFileName() const
{
	return file_name_;
}
