#pragma once
#include "SConfigurationStructures.h"

class IParser
{
public:
	IParser() = default;
	IParser(IParser&) = delete;
	IParser(IParser&&) = delete;
	virtual ~IParser() = default;

	virtual bool Initialize(const std::string&) = 0;

	SServer& GetDefaultServerConfiguration();
	SComunicationSettings& GetDefaultComunicationConfiguration();
	SLogging& GetDefaultLoggingConfiguration();
	STime& GetDefaultTimeConfiguration();
	SThreadPool& GetDefaultThreadPoolConfiguration();
	SHDDInfo& GetDefaultHDDInfoConfiguration();
	SProcessesInfo& GetDefaultProcessInfoConfiguration();

	virtual SServer& TryToGetServerConfigurationFromFile() = 0;
	virtual SComunicationSettings& TryToGetComunicationConfigurationFromFile() = 0;
	virtual SLogging& TryToGetLoggingConfigurationFromFile() = 0;
	virtual STime& TryToGetTimeConfigurationFromFile() = 0;
	virtual SThreadPool& TryToGetThreadPoolConfigurationFromFile() = 0;
	virtual SHDDInfo& TryToGetHDDInfoConfigurationFromFile() = 0;
	virtual SProcessesInfo& TryToGetProcessInfoConfigurationFromFile() = 0;

protected:
	SServer server_;
	SComunicationSettings comunication_settings_;
	SLogging logging_;
	STime time_;
	SThreadPool thread_pool_;
	SHDDInfo hdd_info_;
	SProcessesInfo processes_info_;
};
