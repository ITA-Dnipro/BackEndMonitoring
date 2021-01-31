#include "stdafx.h"

#include "Utils.h"
#include "CJSONFormatter.h"
#include "CJSONFormatSaver.h"

explicit CJSONFormatSaver::CJSONFormatSaver(const std::string& path_to_file) :
	m_path_to_file(path_to_file), m_number_of_spaces(3), 
	num_of_bities_to_last_data(5)
{ };

bool CJSONFormatSaver::TrySaveToFile(const CJSONFormatter& formatted_data) 
const
{
	if (Utils::TryCreateFileIfNotExist(m_path_to_file))
	{
		//write to log??
	}

	std::ofstream JSON_file_to_save(m_path_to_file, std::ios::binary || 
									std::ios::app);

	if (!JSON_file_to_save.is_open())
	{
		return false;
	}
	if (Utils::IsFileEmpty(JSON_file_to_save))
	{
		if (TryWriteToFile(JSON_file_to_save, formatted_data))
		{
			return true;
		}

		return false;
	}
	JSON_file_to_save.seekp(0, JSON_file_to_save.end);

	std::streampos position = JSON_file_to_save.tellp();
	
	JSON_file_to_save.seekp(position - 
		static_cast<std::streampos>(num_of_bities_to_last_data));

	position = JSON_file_to_save.tellp();
	if (!TryWriteToFile(JSON_file_to_save, formatted_data))
	{
		// exception
		return false;
	}
	constexpr char symbol_instead_brace[] = { ',' };
	
	JSON_file_to_save.seekp(position);
	JSON_file_to_save.write(symbol_instead_brace, 1);
	JSON_file_to_save.close();

    return true;
}

bool CJSONFormatSaver::TryWriteToFile(std::ofstream& JSON_file_to_save, 
	const CJSONFormatter& formatted_data) const
{
	if (!JSON_file_to_save.is_open())
	{
		return false;
	}
	JSON_file_to_save << std::setw(m_number_of_spaces) << 
		*formatted_data.GetJSONFormattedData() << std::endl;

	return true;
}
