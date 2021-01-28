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
	bool IsFileInitialized() const override;
	void ReadConfigFromFile() override;
	
private:
	void GetServerConfigurationFromFile()  override;
	void GetComunicationConfigurationFromFile() override;
	void GetLoggingConfigurationFromFile() override;
	void GetTimeConfigurationFromFile() override;
	void GetThreadPoolConfigurationFromFile() override;
	void GetHDDInfoConfigurationFromFile() override;
	void GetProcessInfoConfigurationFromFile() override;

	bool TryToGetStringData(const std::string& data_path, std::string& return_data);
	void SearchNode(const std::string& data_path, pugi::xpath_node& node) const;

	static void FormConfigurationString(std::string& data_to_form);
	static bool TryToConvertToBool(const std::string& data_to_convert, bool& return_data);
	static bool TryToConvertToInt(const std::string& data_to_convert, int& return_data);

private:
	std::unique_ptr<pugi::xml_document> p_file_ = nullptr;
};
