#include "stdafx.h"
#include "XMLParser.h"
#include "pugixml.hpp"

void XMLParser::FormConfigurationString(std::string& return_data) const
{
	return_data = return_data.substr((return_data.find_first_of("\"") + 1), (return_data.find_last_of("\"") - 2));
}

bool XMLParser::TryToGetStringDataFromFile(const std::string& data_path, std::string& return_data) const
{
	pugi::xml_document doc;
	if (doc.load_file(path_to_configuration_file_.c_str()))
	{
		auto point = doc.select_node(data_path.c_str());
		return_data = point.node().child_value();
		FormConfigurationString(return_data);
		return true;
	}

	std::cerr << "Failed to open File!! with this path: " <<
		path_to_configuration_file_ << std::endl;
	return false;
}

bool XMLParser::TryToGetIntegerConfiguration(const std::string& data_path, int& return_data) const
{
	std::string tmp_answer;
	if (TryToGetStringDataFromFile(data_path, tmp_answer))
	{
		return_data = std::stoi(tmp_answer);
		return true;
	}

	return false;
}

bool XMLParser::IsConfigurationEnabled(const std::string& data_path) const
{
	std::string tmp_answer;
	if (TryToGetStringDataFromFile(data_path, tmp_answer))
	{
		return tmp_answer == "enable";
	}

	return false;
}

bool XMLParser::TryToGetStringConfiguration(const std::string& data_path, std::string& return_data) const
{
	return TryToGetStringDataFromFile(data_path, return_data);
}
