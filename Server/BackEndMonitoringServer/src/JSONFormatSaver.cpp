#include "stdafx.h"
#include "JSONFormatSaver.h"

bool JSONFormatSaver::TrySaveToFile(JSONFormatter& formatted_data)
{
    std::ofstream JSON_file_to_save(path_to_save_file_, std::ios::app);

	if (!JSON_file_to_save.is_open())
	{
		return false;
	}

	for (const auto& data_to_save : *formatted_data.GetJSONFormattedData())
	{
		JSON_file_to_save << std::setw(number_of_spaces_) << data_to_save << std::endl;
	}

    return true;
}
