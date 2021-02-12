#include "stdafx.h"

#include "Utils.h"

#include "CFindFileByDateTime.h"

bool CFindFileByDateTime::TryFindFileByValue(
	const std::string& date_time, const std::string& path_to_general_folder, 
	std::string& path_to_file)
{
	m_position = date_time.find_first_of(" ");
	if (m_position == std::string::npos)
	{
		//write to log
		return false;
	}
	m_date = date_time.substr(0, m_position);
	if (!TryFindFileByValueInFolder(m_date, path_to_general_folder, 
			path_to_file))
	{
		// write to log
		return false;
	}
	m_hour = date_time.substr(m_position, 2U);
	if (!TryFindFileByValueInFolder(m_hour, path_to_general_folder,
		path_to_file))
	{
		// write to log
		return false;
	}
	
	return true;
}
