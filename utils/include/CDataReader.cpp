#include "stdafx.h"
#include "CDataReader.h"
#include "CLogger/include/Log.h"

bool CDataReader::TryToConvertToBool(const std::string& data_to_convert, bool& return_data)
{
	const std::string on = "enable";
	const std::string off = "disable";
	if (on == data_to_convert)
	{
		return_data = true;
		return true;
	}
	else if (off == data_to_convert)
	{
		return_data = false;
		return true;
	}
	
	CLOG_ERROR_WITH_PARAMS("Failed to convert to bool", data_to_convert);
	return false;
}

bool CDataReader::TryToConvertToInteger(const std::string& data_to_convert, int& return_data)
{
	CLOG_DEBUG_START_FUNCTION();
		size_t tmp;
		return_data = std::stoi(data_to_convert, &tmp);
		if (data_to_convert.size() != tmp)
			throw std::invalid_argument("Failed to convert data to integer: " + data_to_convert);

		return true;

	CLOG_DEBUG_END_FUNCTION();

	return false;
}
