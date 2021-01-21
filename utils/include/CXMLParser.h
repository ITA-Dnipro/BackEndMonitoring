#pragma once

#include "pugixml.hpp"
#include "IParser.h"

class CXMLParser : public IParser
{
public:
	CXMLParser() = default;
	CXMLParser(CXMLParser&) = delete;
	CXMLParser(CXMLParser&&) = delete;

	~CXMLParser() override = default;

	bool Initialize(const std::string& path_to_configuration_file) override;

	SServer& TryToGetServerConfigurationFromFile() override;
	SComunicationSettings& TryToGetComunicationConfigurationFromFile() override;
	SLogging& TryToGetLoggingConfigurationFromFile() override;
	STime& TryToGetTimeConfigurationFromFile() override;
	SThreadPool& TryToGetThreadPoolConfigurationFromFile() override;
	SHDDInfo& TryToGetHDDInfoConfigurationFromFile() override;
	SProcessesInfo& TryToGetProcessInfoConfigurationFromFile() override;

private:
	static void FormConfigurationString(std::string& data_to_form);
	static bool TryToConvertToBool(const std::string& data_to_convert, bool& return_data);
	static bool TryToConvertToInt(const std::string& data_to_convert, int& return_data);
private:
	std::unique_ptr<pugi::xml_document> p_docfile_;
};
