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
	void ReadConfigFromFile();

	const SServer& GetServerConfiguration() const;
	const SComunicationSettings& GetComunicationConfiguration() const;
	const SLogging& GetLoggingConfiguration() const;
	const STime& GetTimeConfiguration() const;
	const SThreadPool& GetThreadPoolConfiguration() const;
	const SHDDInfo& GetHDDInfoConfiguration() const;
	const SProcessesInfo& GetProcessInfoConfiguration() const;

private:
	bool IsParserInitialized() const;
	std::unique_ptr<IParser> p_parser_ = nullptr;
};