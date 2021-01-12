#pragma once
#include "stdafx.h"

class XMLParser
{
public:
	XMLParser() = delete;
	XMLParser(XMLParser&) = delete;
	XMLParser(XMLParser&&) = delete;

	XMLParser(std::string path_to_configuration_file) :
		path_to_configuration_file_(path_to_configuration_file)
	{ };

	~XMLParser() = default;

	int getIntegerConfiguration(const std::string& data_path) const;
	bool isConfigurationEnabled(const std::string& data_path) const;
	std::string getStringConfiguration(const std::string& data_path) const;

private:
	std::string path_to_configuration_file_;

	std::string formConfigurationString(const std::string& string_to_form) const;
	std::string getStringDataFromFile(const std::string& data_path) const;
};


