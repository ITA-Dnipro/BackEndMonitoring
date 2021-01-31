#include "stdafx.h"
#include "CDataReader.h"

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

	// todo: use logger
	std::cerr << "failed to convert data to bool" << std::endl;
	return false;
}

bool CDataReader::TryToConvertToInteger(const std::string& data_to_convert, int& return_data)
{
	try
	{
		size_t tmp;
		return_data = std::stoi(data_to_convert, &tmp);
		if (data_to_convert.size() != tmp)
			throw std::invalid_argument("Failed to convert data to integer");

		return true;
	}
	catch (const std::exception& e)
	{
		e.what();
		// todo: use logger
	}

	return false;
}
