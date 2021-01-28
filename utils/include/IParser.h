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
	virtual bool IsFileInitialized() const = 0;
	virtual void ReadConfigFromFile() = 0;

	const SServer& GetServerConfiguration() const;
	const SComunicationSettings& GetComunicationConfiguration() const;
	const SLogging& GetLoggingConfiguration() const;
	const STime& GetTimeConfiguration() const;
	const SThreadPool& GetThreadPoolConfiguration() const;
	const SHDDInfo& GetHDDInfoConfiguration() const;
	const SProcessesInfo& GetProcessInfoConfiguration() const;


protected:

	virtual void GetServerConfigurationFromFile() = 0;
	virtual void GetComunicationConfigurationFromFile() = 0;
	virtual void GetLoggingConfigurationFromFile() = 0;
	virtual void GetTimeConfigurationFromFile() = 0;
	virtual void GetThreadPoolConfigurationFromFile() = 0;
	virtual void GetHDDInfoConfigurationFromFile() = 0;
	virtual void GetProcessInfoConfigurationFromFile() = 0;

protected:
	SServer server_;
	SComunicationSettings comunication_settings_;
	SLogging logging_;
	STime time_;
	SThreadPool thread_pool_;
	SHDDInfo hdd_info_;
	SProcessesInfo processes_info_;
};
