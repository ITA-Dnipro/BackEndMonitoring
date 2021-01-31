#include "stdafx.h"
#include "CComunicationSettings.h"

CComunicationSettings::CComunicationSettings(std::shared_ptr<CDataReader> p_data_reader) : p_data_reader_(p_data_reader)
{

}

void CComunicationSettings::ReadConfigurationFromFile()
{
	if (nullptr == p_data_reader_ || !p_data_reader_->IsFileInitialized())
	{
		// write to logger
		return;
	}

	std::string tmp_string;
	int tmp_int = 0;
	bool tmp_bool = false;

	if (p_data_reader_->TryToGetStringData("//root/communicationsettings/blocking", tmp_string))
		blocking_ = CDataReader::TryToConvertToBool(tmp_string, tmp_bool) ? tmp_bool : blocking_;

	if (p_data_reader_->TryToGetStringData("//root/communicationsettings/socket_timeout", tmp_string))
		socket_timeout_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int) ? tmp_int : socket_timeout_;

}

bool CComunicationSettings::GetBlocking() const
{
	return blocking_;
}

int CComunicationSettings::GetSocketTimeout() const
{
	return socket_timeout_;
}



