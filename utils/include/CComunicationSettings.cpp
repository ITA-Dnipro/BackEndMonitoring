#include "stdafx.h"
#include "CComunicationSettings.h"
#include "CLogger/include/Log.h"

CComunicationSettings::CComunicationSettings(std::shared_ptr<CDataReader> p_data_reader) :
	p_data_reader_(p_data_reader)
{

}

void CComunicationSettings::ReadConfigurationFromFile()
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

	if (p_data_reader_->TryToGetStringData("//root/communicationsettings/blocking", tmp_string))
		blocking_ = CDataReader::TryToConvertToBool(tmp_string, tmp_bool) ? tmp_bool : blocking_;

	if (p_data_reader_->TryToGetStringData("//root/communicationsettings/socket_timeout", tmp_string))
		socket_timeout_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int) ? tmp_int : socket_timeout_;
	
	CLOG_DEBUG_END_FUNCTION();
}

bool CComunicationSettings::GetBlocking() const
{
	return blocking_;
}

int CComunicationSettings::GetSocketTimeout() const
{
	return socket_timeout_;
}



