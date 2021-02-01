#pragma once
#include "CDataReader.h"
#include "CSettings.h"

class CServerSettings : public CSettings
{
public:
	CServerSettings() = delete;
	CServerSettings(const CServerSettings&) = delete;
	CServerSettings(CServerSettings&&) = delete;

	explicit CServerSettings(std::shared_ptr<CDataReader> p_data_reader);
	~CServerSettings() override = default;

	void ReadConfigurationFromFile() override;

	[[nodiscard]] std::string GetServerName() const;
	[[nodiscard]] std::string GetServerDisplayName() const;
	[[nodiscard]] std::string GetServerIpAddress() const;
	[[nodiscard]] int GetListenerPort() const;

private:
	std::string m_server_displayname_;
	std::string m_ip_address_;
	std::string m_server_name_;
	int m_listener_port_;

};
