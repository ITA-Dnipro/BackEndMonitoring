#include "stdafx.h"
#include "CServerSettings.h"
#include "CLogger/include/Log.h"

CServerSettings::CServerSettings(std::shared_ptr<CDataReader> p_data_reader) :
	p_data_reader_(p_data_reader), server_displayname_("ServTestserver"), ip_address_("127.0.0.1"),
	server_name_("ServTest"), listener_port_(25000)
{

}

void CServerSettings::ReadConfigurationFromFile()
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

	if (p_data_reader_->TryToGetStringData("//root/Server/servername", tmp_string))
		server_name_ = tmp_string != "" ? tmp_string : server_name_;

	if (p_data_reader_->TryToGetStringData("//root/Server/serverdisplayname", tmp_string))
		server_displayname_ = tmp_string != "" ? tmp_string : server_displayname_;

	if (p_data_reader_->TryToGetStringData("//root/Server/listenerport", tmp_string))
		listener_port_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int) ? tmp_int : listener_port_;

	if (p_data_reader_->TryToGetStringData("//root/Server/ipaddress", tmp_string))
		ip_address_ = tmp_string != "" ? tmp_string : ip_address_;

	CLOG_DEBUG_END_FUNCTION();
}

std::string CServerSettings::GetServerName() const
{
	return server_name_;
}

std::string CServerSettings::GetServerDisplayName() const
{
	return server_displayname_;
}

std::string CServerSettings::GetServerIpAddress() const
{
	return ip_address_;
}

int CServerSettings::GetListenerPort() const
{
	return listener_port_;
}


