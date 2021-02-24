#pragma once
#include "CDataReader.h"
#include "CLogger/include/Log.h"
#include "CSettings.h"

class CLoggingSettings : public CSettings
{
public:
	CLoggingSettings() = delete;
	CLoggingSettings(CLoggingSettings&) = delete;
	CLoggingSettings(CLoggingSettings&&) = delete;
	
	explicit CLoggingSettings(std::shared_ptr<CDataReader> p_data_reader);
	~CLoggingSettings() override = default;

	void ReadConfigurationFromFile() override;

	[[nodiscard]] ELogLevel GetLogLevel() const;
	[[nodiscard]] ELogFlush GetFlush() const;
	[[nodiscard]] std::string GetFileName() const;

private:
	ELogLevel m_log_level_;
	ELogFlush m_log_flush_;
	std::string m_file_name_;
	
};