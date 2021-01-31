#pragma once
#include "CLogger/include/Log.h"
#include "CDataReader.h"

class CLoggingSettings
{
public:
	CLoggingSettings() = delete;
	CLoggingSettings(CLoggingSettings&) = delete;
	CLoggingSettings(CLoggingSettings&&) = delete;

	CLoggingSettings(std::shared_ptr<CDataReader> p_data_reader);
	~CLoggingSettings() = default;

	void ReadConfigurationFromFile();

	[[nodiscard]] ELogLevel GetServerName() const;
	[[nodiscard]] std::string GetServerDisplayName() const;
	[[nodiscard]] std::string GetServerIpAddress() const;
	[[nodiscard]] int GetListenerPort() const;

private:
	std::shared_ptr<CDataReader> p_data_reader_;
	ELogLevel log_level_ = static_cast<ELogLevel>(1);
	ELog
	std::string file_name_ = "serverlog.txt";

	
};