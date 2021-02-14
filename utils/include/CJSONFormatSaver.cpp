#include "stdafx.h"

#include <fstream>

#include "Utils.h"
#include "CJSONFormatter.h"
#include "CJSONFormatSaver.h"
#include "CLogger/include/Log.h"

CJSONFormatSaver::CJSONFormatSaver(const std::filesystem::path& path_to_file) :
	m_path_to_file(path_to_file), m_number_of_spaces(3),
	m_bytes_to_last_data(3)
{
	CLOG_DEBUG_START_FUNCTION( );
	CLOG_DEBUG_END_FUNCTION( );
};

bool CJSONFormatSaver::TrySaveToFile(const CJSONFormatter& formatted_data)
const
{
	CLOG_DEBUG_START_FUNCTION( );
	if (Utils::TryCreateFileIfNotExist(m_path_to_file))
	{
		CLOG_DEBUG("New file created");
	}
	else
	{
		CLOG_ERROR("Can't create new file");
	}
	std::ofstream JSON_file_to_save(m_path_to_file, std::ios::binary |
									std::ios_base::in);
	CLOG_TRACE_VAR_CREATION(JSON_file_to_save);

	if (!JSON_file_to_save.is_open( ))
	{
		CLOG_ERROR("Can't open file");
		return false;
	}
	if (Utils::IsFileEmpty(JSON_file_to_save))
	{
		if (TryWriteToFile(JSON_file_to_save, formatted_data))
		{
			return true;
		}
		CLOG_ERROR("Can't write to file");
		return false;
	}
	JSON_file_to_save.seekp(0, std::ios::end);

	std::streampos position = JSON_file_to_save.tellp( );
	CLOG_TRACE_VAR_CREATION(position);
	JSON_file_to_save.seekp(position -
							static_cast<std::streampos>(m_bytes_to_last_data));

	position = JSON_file_to_save.tellp( );
	if (!TryWriteToFile(JSON_file_to_save, formatted_data))
	{
		CLOG_ERROR("Can't write to file");
		return false;
	}
	constexpr char symbol_instead_brace[] = { ',' };
	CLOG_TRACE_VAR_CREATION(symbol_instead_brace);
	JSON_file_to_save.seekp(position);
	JSON_file_to_save.write(symbol_instead_brace, 1);
	JSON_file_to_save.close( );
	CLOG_DEBUG_END_FUNCTION( );
	return true;
}

bool CJSONFormatSaver::TrySaveToFile(const CJSONFormatter& formatted_data,
									 std::streampos& block_begin, std::streampos& block_end) const
{
	CLOG_DEBUG_START_FUNCTION( );
	if (Utils::TryCreateFileIfNotExist(m_path_to_file))
	{
		CLOG_DEBUG("New file created");
	}
	else
	{
		CLOG_ERROR("Can't create new file");
	}

	std::ofstream JSON_file_to_save(m_path_to_file, std::ios::binary |
									std::ios_base::in);
	CLOG_TRACE_VAR_CREATION(JSON_file_to_save);

	if (!JSON_file_to_save.is_open( ))
	{
		CLOG_ERROR("Can't open file");
		return false;
	}
	if (Utils::IsFileEmpty(JSON_file_to_save))
	{
		if (TryWriteToFile(JSON_file_to_save, formatted_data))
		{
			unsigned short bytes_to_next_line = 2;
			JSON_file_to_save.seekp(0, std::ios::beg);
			block_begin = JSON_file_to_save.tellp( );
			block_begin += static_cast<std::streampos>(
				bytes_to_next_line + m_number_of_spaces);

			JSON_file_to_save.seekp(0, std::ios::end);
			block_end = JSON_file_to_save.tellp( );
			block_end -= m_bytes_to_last_data;

			return true;
		}
		CLOG_ERROR("Can't write to file");
		return false;
	}
	JSON_file_to_save.seekp(0, std::ios::end);

	std::streampos position = JSON_file_to_save.tellp( );
	CLOG_TRACE_VAR_CREATION(position);
	JSON_file_to_save.seekp(position -
							static_cast<std::streampos>(m_bytes_to_last_data));

	position = JSON_file_to_save.tellp( );
	if (!TryWriteToFile(JSON_file_to_save, formatted_data))
	{
		CLOG_ERROR("Can't write to file");
		return false;
	}
	block_end = JSON_file_to_save.tellp( );
	block_end -= m_bytes_to_last_data;

	constexpr char symbol_instead_brace[] = { ',' };
	CLOG_TRACE_VAR_CREATION(symbol_instead_brace);
	JSON_file_to_save.seekp(position);
	JSON_file_to_save.write(symbol_instead_brace, 1);
	
	block_begin = JSON_file_to_save.tellp();
	block_begin += 1ll + m_number_of_spaces;

	JSON_file_to_save.close( );
	CLOG_DEBUG_END_FUNCTION();
	return true;
}

bool CJSONFormatSaver::TryWriteToFile(std::ofstream& JSON_file_to_save,
	const CJSONFormatter& formatted_data) const
{
	CLOG_DEBUG_START_FUNCTION();
	if (!JSON_file_to_save.is_open() || 
		nullptr == formatted_data.GetJSONFormattedData())
	{
		CLOG_WARNING("Error with file writing");
		return false;
	}
	nlohmann::json temp_array;
	temp_array.push_back(*formatted_data.GetJSONFormattedData());
	JSON_file_to_save <<std::setw(m_number_of_spaces) << 
		 temp_array << std::endl;
	CLOG_DEBUG_END_FUNCTION();
	return true;
}
