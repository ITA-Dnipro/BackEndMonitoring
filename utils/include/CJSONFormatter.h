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
		const nlohmann::json& formatted_data);
	[[nodiscard]] bool TrySetJSONFormattedData(
		const nlohmann::json& formatted_data);
	[[nodiscard]] nlohmann::json* GetJSONFormattedData();

protected:
	template <typename Value>
	nlohmann::json CreatePair(const char* name_key, const Value& value_for_key)
	{
		nlohmann::json pair;
		pair[name_key] = value_for_key;
		return pair;
	}

private:
	nlohmann::json m_formatted_data{};
};

