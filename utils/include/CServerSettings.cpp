#include "stdafx.h"
#include "CServerSettings.h"
#include "CLogger/include/Log.h"

CServerSettings::CServerSettings(std::shared_ptr<CDataReader> p_data_reader) :
	CSettings(p_data_reader), m_server_displayname_("ServTestserver"), m_ip_address_("127.0.0.1"),
	m_server_name_("ServTest"), m_listener_port_(25000), m_blocking_(true), m_socket_timeout_(5)
{

}

void CServerSettings::ReadConfigurationFromFile()
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
	bool tmp_bool = false;
	CLOG_TRACE_VAR_CREATION(tmp_int);

	if (m_p_data_reader_->TryToGetStringData("//root/Server/servername", tmp_string))
		m_server_name_ = tmp_string != "" ? tmp_string : m_server_name_;

	if (m_p_data_reader_->TryToGetStringData("//root/Server/serverdisplayname", tmp_string))
		m_server_displayname_ = tmp_string != "" ? tmp_string : m_server_displayname_;

	if (m_p_data_reader_->TryToGetStringData("//root/Server/listenerport", tmp_string))
		m_listener_port_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int) ? tmp_int : m_listener_port_;

	if (m_p_data_reader_->TryToGetStringData("//root/Server/ipaddress", tmp_string))
		m_ip_address_ = tmp_string != "" ? tmp_string : m_ip_address_;

	if (m_p_data_reader_->TryToGetStringData("//root/communicationsettings/blocking", tmp_string))
		m_blocking_ = CDataReader::TryToConvertToBool(tmp_string, tmp_bool) ? tmp_bool : m_blocking_;

	if (m_p_data_reader_->TryToGetStringData("//root/communicationsettings/socket_timeout", tmp_string))
		m_socket_timeout_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int) ? tmp_int : m_socket_timeout_;

	CLOG_DEBUG_END_FUNCTION();
}

std::string CServerSettings::GetServerName() const
{
	return m_server_name_;
}

std::string CServerSettings::GetServerDisplayName() const
{
	return m_server_displayname_;
}

std::string CServerSettings::GetServerIpAddress() const
{
	return m_ip_address_;
}

int CServerSettings::GetListenerPort() const
{
	return m_listener_port_;
}

bool CServerSettings::GetBlocking() const
{
	return m_blocking_;
}

int CServerSettings::GetSocketTimeout() const
{
	return m_socket_timeout_;
}

