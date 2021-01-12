#include "stdafx.h"
#include "XMLParser.h"
#include "pugixml.hpp"

std::string XMLParser::formConfigurationString(const std::string& string_to_form) const
{
	return string_to_form.substr((string_to_form.find_first_of("\"") + 1), (string_to_form.find_last_of("\"") - 2));
}

std::string XMLParser::getStringDataFromFile(const std::string& data_path) const
{
	pugi::xml_document doc;
	if (doc.load_file(path_to_configuration_file_.c_str()))
	{
		auto point = doc.select_node(data_path.c_str());
		return formConfigurationString(point.node().child_value());
	}

	std::cerr << "Failed to open File!! with this path: " <<
		path_to_configuration_file_ << std::endl;
	return "";
}

int XMLParser::getIntegerConfiguration(const std::string& data_path) const
{
	std::string data = getStringDataFromFile(data_path);
	return data.size() > 0 ? std::stoi(data) : -1;
}

bool XMLParser::isConfigurationEnabled(const std::string& data_path) const
{
	return getStringDataFromFile(data_path) == "enabled" ? true : false;
}

std::string XMLParser::getStringConfiguration(const std::string& data_path) const
{
	return getStringDataFromFile(data_path);
}
