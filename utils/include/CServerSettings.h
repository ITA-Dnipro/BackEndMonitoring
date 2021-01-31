#pragma once
#include "CDataReader.h"

class CServerSettings
{
public:
	CServerSettings() = delete;
	CServerSettings(CServerSettings&) = delete;
	CServerSettings(CServerSettings&&) = delete;

	CServerSettings(std::shared_ptr<CDataReader> p_data_reader);
	~CServerSettings() = default;

	void ReadConfigurationFromFile();

	[[nodiscard]] std::string GetServerName() const;
	[[nodiscard]] std::string GetServerDisplayName() const;
	[[nodiscard]] std::string GetServerIpAddress() const;
	[[nodiscard]] int GetListenerPort() const;

private:
	std::shared_ptr<CDataReader> p_data_reader_;

	std::string server_displayname_ = ;
	std::string ip_address_ = "127.0.0.1";
	std::string server_name_ = "ServTest";
	int listener_port_ = 25000;

};
