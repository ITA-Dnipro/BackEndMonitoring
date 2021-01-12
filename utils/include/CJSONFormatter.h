#pragma once
#include "json.hpp"

class CJSONFormatter
{
public:
	CJSONFormatter() = default;
	CJSONFormatter(const CJSONFormatter& orig) : m_formatted_data_(orig.m_formatted_data_)
	{ };
	CJSONFormatter(const CJSONFormatter&&) = delete;

	bool TryAddJSONFormattedData(const nlohmann::json* formatted_data);
	bool TrySetJSONFormattedData(const nlohmann::json* formatted_data);

	nlohmann::json* GetJSONFormattedData();

protected:
	nlohmann::json m_formatted_data_{};
};

