#include "stdafx.h"
#include "CComunicationSettings.h"
#include "CLogger/include/Log.h"

CComunicationSettings::CComunicationSettings(std::shared_ptr<CDataReader> p_data_reader) :
	m_p_data_reader_(p_data_reader), m_blocking_(false), m_socket_timeout_(5)
{

}

void CComunicationSettings::ReadConfigurationFromFile()
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

	if (m_p_data_reader_->TryToGetStringData("//root/communicationsettings/blocking", tmp_string))
		m_blocking_ = CDataReader::TryToConvertToBool(tmp_string, tmp_bool) ? tmp_bool : m_blocking_;

	if (m_p_data_reader_->TryToGetStringData("//root/communicationsettings/socket_timeout", tmp_string))
		m_socket_timeout_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int) ? tmp_int : m_socket_timeout_;
	
	CLOG_DEBUG_END_FUNCTION();
}

bool CComunicationSettings::GetBlocking() const
{
	return m_blocking_;
}

int CComunicationSettings::GetSocketTimeout() const
{
	return m_socket_timeout_;
}



