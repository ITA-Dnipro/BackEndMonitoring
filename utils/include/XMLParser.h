#pragma once

class XMLParser
{
public:
	XMLParser() = default;
	XMLParser(XMLParser&) = delete;
	XMLParser(XMLParser&&) = delete;

	~XMLParser() = default;

	bool Initialize(const std::string& paht_to_configuration_file);

	bool IsConfigurationEnabled(const std::string& data_path, bool& return_data) const;

	bool TryToGetIntegerConfiguration(const std::string& data_path, int& return_data) const;
	bool TryToGetStringConfiguration(const std::string& data_path, std::string& return_data) const;

private:
	bool TryToGetStringDataFromFile(const std::string& data_path, std::string& return_data) const;
	void FormConfigurationString(std::string& data_to_form) const;

private:
	std::unique_ptr<pugi::xml_document> p_docfile;
};


