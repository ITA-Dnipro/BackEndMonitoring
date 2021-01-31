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
	std::shared_ptr<CDataReader> p_data_reader_;
	ELogLevel log_level_;
	ELogFlush log_flush_;
	std::string file_name_;
	
};