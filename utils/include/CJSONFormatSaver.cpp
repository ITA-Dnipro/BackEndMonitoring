#include "stdafx.h"

#include "json.hpp"

#include "CJSONFormatSaver.h"
#include "Utils.h"

bool CJSONFormatSaver::TrySaveToFile(CJSONFormatter& formatted_data)
{
	std::ifstream json_file_to_read;
	json_file_to_read.open(m_path_to_file);
	nlohmann::json buff;
	if (Utils::IsFileEmpty(json_file_to_read))
	{
		buff = *formatted_data.GetJSONFormattedData();
	}
	else
	{
		json_file_to_read >> buff;
	}
	json_file_to_read.close();
	if (!buff.is_null())
	{
		buff.merge_patch(*formatted_data.GetJSONFormattedData());
	}
	std::ofstream JSON_file_to_save(m_path_to_file);

	if (!JSON_file_to_save.is_open())
	{
		return false;
	}
	JSON_file_to_save << std::setw(m_number_of_spaces) << buff << std::endl;

    return true;
}
