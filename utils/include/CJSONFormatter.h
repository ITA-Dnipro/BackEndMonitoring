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
	[[nodiscard]] const nlohmann::json* GetJSONFormattedData() const;

	[[nodiscard]] bool TryGetJSONDataAsString(std::string& str_for_data);

	[[nodiscard]] bool TryEraseAllData();

	[[nodiscard]] bool TryReloadDateAndTime();

protected:
	template <typename Value>
	nlohmann::json CreatePair(const char* name_key, const Value& value_for_key)
	{
		return {name_key, value_for_key};
	}

private:
	nlohmann::json m_formatted_data{};
	std::optional<std::string> m_date_and_time;
};

