#pragma once

#include "IParser.h"
#include "SConfigurationStructures.h"

class CConfiguration
{
public:
	CConfiguration() = delete;
	CConfiguration(CConfiguration&) = delete;
	CConfiguration(CConfiguration&&) = delete;



	explicit CConfiguration(std::unique_ptr<IParser> p_parser);

	SServer& GetDefaultServerConfiguration();
	SComunicationSettings& GetDefaultComunicationConfiguration();
	SLogging& GetDefaultLoggingConfiguration();
	STime& GetDefaultTimeConfiguration();
	SThreadPool& GetDefaultThreadPoolConfiguration();
	SHDDInfo& GetDefaultHDDInfoConfiguration();
	SProcessesInfo& GetDefaultProcessInfoConfiguration();

	SServer& TryToGetServerConfigurationFromFile();
	SComunicationSettings& TryToGetComunicationConfigurationFromFile();
	SLogging& TryToGetLoggingConfigurationFromFile();
	STime& TryToGetTimeConfigurationFromFile();
	SThreadPool& TryToGetThreadPoolConfigurationFromFile();
	SHDDInfo& TryToGetHDDInfoConfigurationFromFile();
	SProcessesInfo& TryToGetProcessInfoConfigurationFromFile();

private:
	std::unique_ptr<IParser> p_parser_;
};