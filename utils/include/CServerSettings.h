#pragma once
#include "CDataReader.h"

class CServerSettings
{
public:
	CServerSettings() = delete;
	CServerSettings(const CServerSettings&) = delete;
	CServerSettings(CServerSettings&&) = delete;

	explicit CServerSettings(std::shared_ptr<CDataReader> p_data_reader);
	~CServerSettings() = default;

	void ReadConfigurationFromFile();

	[[nodiscard]] std::string GetServerName() const;
	[[nodiscard]] std::string GetServerDisplayName() const;
	[[nodiscard]] std::string GetServerIpAddress() const;
	[[nodiscard]] int GetListenerPort() const;

private:
	std::shared_ptr<CDataReader> p_data_reader_;

	std::string server_displayname_;
	std::string ip_address_;
	std::string server_name_;
	int listener_port_;

};
