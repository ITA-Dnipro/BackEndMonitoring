#include "stdafx.h"
#include "CJSONFormatSaver.h"

bool CJSONFormatSaver::TrySaveToFile(CJSONFormatter& formatted_data)
{
	std::ifstream json_file_to_read;
	json_file_to_read.open(m_path_to_file_);
	nlohmann::json buff;
	if (!json_file_to_read.eof())
	{
		buff = *formatted_data.GetJSONFormattedData();
	}
	else
	{
		json_file_to_read >> buff;
	}
	json_file_to_read.close();

	if (buff.is_null())
	{
		buff.merge_patch(*formatted_data.GetJSONFormattedData());
	}


    std::ofstream JSON_file_to_save(m_path_to_file_);

	if (!JSON_file_to_save.is_open())
	{
		return false;
	}


	JSON_file_to_save << std::setw(m_number_of_spaces_) << buff << std::endl;

    return true;
}
