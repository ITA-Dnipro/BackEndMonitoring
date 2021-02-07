#include "stdafx.h"

#include <fstream>

#include "Utils.h"
#include "CJSONFormatter.h"
#include "CJSONFormatSaver.h"
#include "CLogger/include/Log.h"

CJSONFormatSaver::CJSONFormatSaver(const std::string& path_to_file) :
	m_path_to_file(path_to_file), m_number_of_spaces(3),
	m_num_of_bities_to_last_data(3)
{ };

bool CJSONFormatSaver::TrySaveToFile(const CJSONFormatter& formatted_data)
const
{
	CLOG_DEBUG_START_FUNCTION(); 
	if (Utils::TryCreateFileIfNotExist(m_path_to_file))
	{
		//write to log??
	}

	std::ofstream JSON_file_to_save(m_path_to_file, std::ios::binary |
									std::ios_base::in);
	CLOG_TRACE_VAR_CREATION(JSON_file_to_save);

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
	CLOG_TRACE_VAR_CREATION(position);
	JSON_file_to_save.seekp(position -
		static_cast<std::streampos>(m_num_of_bities_to_last_data));

	position = JSON_file_to_save.tellp();
	if (!TryWriteToFile(JSON_file_to_save, formatted_data))
	{
		// exception
		return false;
	}
	constexpr char symbol_instead_brace[] = { ',' };
	CLOG_TRACE_VAR_CREATION(symbol_instead_brace);
	JSON_file_to_save.seekp(position);
	JSON_file_to_save.write(symbol_instead_brace, 1);
	JSON_file_to_save.close();
	CLOG_DEBUG_END_FUNCTION();
    return true;
}

bool CJSONFormatSaver::TryWriteToFile(std::ofstream& JSON_file_to_save,
	const CJSONFormatter& formatted_data) const
{
	CLOG_DEBUG_START_FUNCTION();
	if (!JSON_file_to_save.is_open())
	{
		return false;
	}
	JSON_file_to_save << std::setw(m_number_of_spaces) <<
		*formatted_data.GetJSONFormattedData() << std::endl;
	CLOG_DEBUG_END_FUNCTION();
	return true;
}
