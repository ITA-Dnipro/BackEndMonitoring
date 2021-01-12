#pragma once

#include "json.hpp"

class CJSONFormatter
{
public:
	CJSONFormatter() = default;
	CJSONFormatter(const CJSONFormatter& orig) : 
		m_formatted_data(orig.m_formatted_data)
	{ };
	CJSONFormatter(const CJSONFormatter&&) = delete;

	[[nodiscard]] bool TryAddJSONFormattedData(
		const nlohmann::json* formatted_data);
	[[nodiscard]] bool TrySetJSONFormattedData(
		const nlohmann::json* formatted_data);
	[[nodiscard]] nlohmann::json* GetJSONFormattedData();

protected:
	nlohmann::json m_formatted_data{};
};

