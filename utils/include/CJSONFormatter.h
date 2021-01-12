#pragma once

#include "stdafx.h"
#include "Utilities.h"

class CJSONFormatter
{
public:
	CJSONFormatter() = default;
	CJSONFormatter(CJSONFormatter& orig) : m_formatted_data_(orig.m_formatted_data_)
	{ };
	CJSONFormatter(CJSONFormatter&&) = delete;

	bool TryAddJSONFormattedData(const nlohmann::json* formatted_data);
	bool TrySetJSONFormattedData(const nlohmann::json* formatted_data);

	nlohmann::json* GetJSONFormattedData();

protected:
	nlohmann::json m_formatted_data_{};
};

