#include "stdafx.h"
#include "XMLParser.h"
#include "pugixml.hpp"

bool XMLParser::Initialize(const std::string& paht_to_configuration_file)
{
	p_docfile = std::move(std::make_unique<pugi::xml_document>());
	return p_docfile->load_file(paht_to_configuration_file.c_str());
}

bool XMLParser::IsConfigurationEnabled(const std::string& data_path, bool& return_data) const
{
	std::string tmp_answer;
	if (TryToGetStringDataFromFile(data_path, tmp_answer))
	{
		return_data = (tmp_answer == "enable");
		return true;
	}

	return false;
}

bool XMLParser::TryToGetIntegerConfiguration(const std::string& data_path, int& return_data) const
{
	try
	{
		std::string tmp_answer;
		if (TryToGetStringDataFromFile(data_path, tmp_answer))
		{
			size_t pos;
			return_data = std::stoi(tmp_answer, &pos);
			if (tmp_answer.size() != pos)
			{
				throw std::invalid_argument("Failed to convert data to integer with this path: " + data_path);
			}
			return true;
		}
	}
	catch (std::logic_error& e)
	{
		std::cerr << e.what();
	}

	return false;
}


bool XMLParser::TryToGetStringConfiguration(const std::string& data_path, std::string& return_data) const
{
	return TryToGetStringDataFromFile(data_path, return_data);
}

bool XMLParser::TryToGetStringDataFromFile(const std::string& data_path, std::string& return_data) const
{
	try
	{
		auto point = p_docfile->select_node(data_path.c_str());
		return_data = point.node().child_value();
		FormConfigurationString(return_data);
		return true;
	}
	catch (std::bad_alloc& e)
	{

		std::cerr << e.what() << " Failed to find data!! with this path: " <<
			data_path << std::endl;

	}

	return false;
}

void XMLParser::FormConfigurationString(std::string& return_data) const
{
	return_data = return_data.substr((return_data.find_first_of("\"") + 1), (return_data.find_last_of("\"") - 2));
}