#pragma once
#include "CDataReader.h"
#include "CLogger/include/Log.h"

class CLoggingSettings
{
public:
	CLoggingSettings() = delete;
	CLoggingSettings(CLoggingSettings&) = delete;
	CLoggingSettings(CLoggingSettings&&) = delete;
	
	explicit CLoggingSettings(std::shared_ptr<CDataReader> p_data_reader);
	~CLoggingSettings() = default;

	void ReadConfigurationFromFile();

	[[nodiscard]] ELogLevel GetLogLevel() const;
	[[nodiscard]] ELogFlush GetFlush() const;
	[[nodiscard]] std::string GetFileName() const;

private:
	std::shared_ptr<CDataReader> m_p_data_reader_;
	ELogLevel m_log_level_;
	ELogFlush m_log_flush_;
	std::string m_file_name_;
	
};