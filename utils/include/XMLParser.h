#pragma once

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

	bool IsConfigurationEnabled(const std::string& data_path) const;

	bool TryToGetIntegerConfiguration(const std::string& data_path, int& return_data) const;
	bool TryToGetStringConfiguration(const std::string& data_path, std::string& return_data) const;

private:
	bool TryToGetStringDataFromFile(const std::string& data_path, std::string& return_data) const;
	void FormConfigurationString(std::string& data_to_form) const;

private:
	std::string path_to_configuration_file_;
};


