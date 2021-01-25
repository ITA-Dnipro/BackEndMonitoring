#include "stdafx.h"

#include "Utils.h"
#include "CJSONFormatter.h"
#include "CJSONFormatSaver.h"

CJSONFormatSaver::CJSONFormatSaver(const std::string& path_to_file) :
	m_path_to_file(path_to_file), m_number_of_spaces(3)
{ };

bool CJSONFormatSaver::TrySaveToFile(CJSONFormatter& formatted_data)
{
	if (Utils::TryCreateFileIfNotExist(m_path_to_file))
	{
		//write to log??
	}

	std::ofstream JSON_file_to_save(m_path_to_file, std::ios::binary || 
									std::ios::app);

	if (!JSON_file_to_save.is_open())
	{
		JSON_file_to_save.close();
		return false;
	}
	if (Utils::IsFileEmpty(JSON_file_to_save))
	{
		if (TryWriteToFile(JSON_file_to_save, formatted_data))
		{
			JSON_file_to_save.close();
			return true;
		}
		JSON_file_to_save.close();
		return false;
	}
	JSON_file_to_save.seekp(0, JSON_file_to_save.end);

	std::streampos position = JSON_file_to_save.tellp();

	JSON_file_to_save.seekp(position - static_cast<std::streampos>(5));
	char a[] = { ',' };

	JSON_file_to_save.write(a, 1);
	position = JSON_file_to_save.tellp();
	if (!TryWriteToFile(JSON_file_to_save, formatted_data))
	{
		JSON_file_to_save.close();
		// exception
		return false;
	}
	char b[] = { ' ' };

	JSON_file_to_save.seekp(position);
	JSON_file_to_save.write(b, 1);
	JSON_file_to_save.close();
    return true;
}

bool CJSONFormatSaver::TryWriteToFile(std::ofstream& JSON_file_to_save, 
	CJSONFormatter& formatted_data)
{
	if (!JSON_file_to_save.is_open())
	{
		return false;
	}
	JSON_file_to_save << std::setw(m_number_of_spaces) << 
		*formatted_data.GetJSONFormattedData() << std::endl;

	return true;
}
