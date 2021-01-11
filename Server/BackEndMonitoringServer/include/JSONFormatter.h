#pragma once

#include "stdafx.h"

class JSONFormatter
{
public:
	JSONFormatter() = delete;
	JSONFormatter(JSONFormatter& orig) : formatted_data_(orig.formatted_data_)
	{ };
	JSONFormatter(JSONFormatter&&) = delete;

	static JSONFormatter* FactoryJSONFormatter();

	bool AddNewPair(std::string key, nlohmann::json value);
	
	std::vector<nlohmann::json>* GetJSONFormattedData();

	JSONFormatter(const std::string& time_of_checking_status) : 
		formatted_data_({ time_of_checking_status })
	{ };
protected:

	std::vector<nlohmann::json> formatted_data_;
};

