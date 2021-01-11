#pragma once

#include "stdafx.h"

#include "Utilities.h"

class JSONFormatter
{
public:
	JSONFormatter() = default;
	JSONFormatter(JSONFormatter& orig) : formatted_data_(orig.formatted_data_)
	{ };
	JSONFormatter(JSONFormatter&&) = delete;

	bool TryAddJSONFormattedData(const nlohmann::json* formatted_data);
	bool TrySetJSONFormattedData(const nlohmann::json* formatted_data);

	nlohmann::json* GetJSONFormattedData();

protected:
	nlohmann::json formatted_data_{};
};

