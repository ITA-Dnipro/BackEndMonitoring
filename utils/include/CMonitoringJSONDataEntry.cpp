#include "stdafx.h"

#include "Utils.h"
#include "CReadFileWrapper.h"
#include "Log.h"

#include "CMonitoringJSONDataEntry.h"

CMonitoringJSONDataEntry::CMonitoringJSONDataEntry(
	const std::filesystem::path& path_to_file, 
	std::streampos block_start, std::streampos block_end,
	time_t date_time,const std::string& date_format)
	: m_path_to_file(path_to_file), m_block_start(block_start),
	  m_block_end(block_end), m_date_and_time(date_time),
	  m_date_format(date_format)
	  
{
	CLOG_TRACE_START_FUNCTION( );
	CLOG_TRACE_END_FUNCTION( );
}

bool CMonitoringJSONDataEntry::Initialize()
{
	bool success = true;
	CLOG_TRACE_START_FUNCTION( );
	success = CheckData();
	CLOG_TRACE_END_FUNCTION_WITH_RETURN(success);
	return success;
}

bool CMonitoringJSONDataEntry::GetInfo(std::string& info)
{
	bool success = true;
	CLOG_TRACE_START_FUNCTION( );

	do
	{
		CReadFileWrapper file(m_path_to_file);
		if (!file.Initialize( ))
		{
			CLOG_ERROR("Can't initialize fstream");
			success = false;
			break;
		}

		if (!file.MoveCursorTo(m_block_start))
		{
			CLOG_ERROR("Can't move cursor in file");
			success = false;
			break;
		}

		if (!file.Read(info, m_block_end - m_block_start))
		{
			CLOG_ERROR("Can't read info from fstream");
			success = false;
			break;
		}
	} while (false);

	CLOG_TRACE_END_FUNCTION_WITH_RETURN(success);
	return success;
}

bool CMonitoringJSONDataEntry::GetDate(time_t& date_and_time)
{
	CLOG_TRACE_START_FUNCTION( );
	date_and_time = m_date_and_time;
	CLOG_TRACE_END_FUNCTION();
	return date_and_time > 0;
}

bool CMonitoringJSONDataEntry::CheckData()
{
	bool success = true;
	CLOG_TRACE_START_FUNCTION( );

	do
	{
		std::string date_str;
		if (!FindDateField(m_block_start, date_str))
		{
			CLOG_ERROR("Can't find dete field of data entry");
			success = false;
			break;
		}

		time_t date;
		if (!FormatDateFromLine(date_str, date))
		{
			CLOG_ERROR("Can't convert string to date");
			success = false;
			break;
		}
		if (!(date == m_date_and_time))
		{
			CLOG_ERROR("Dates isn't equal");
			success = false;
			break;
		}

		std::streampos end_of_block;
		if (!FindEndOfJSONBlock(m_block_start, end_of_block))
		{
			CLOG_ERROR("Can't find end of JSON block");
			success = false;
			break;
		}
		if (!(m_block_end == end_of_block))
		{
			CLOG_ERROR("Ends of JSON block insn't equal");
			success = false;
			break;
		}
	} while (false);
	CLOG_TRACE_END_FUNCTION_WITH_RETURN(success);
	return success;
}

bool CMonitoringJSONDataEntry::FindEndOfJSONBlock(std::streampos start_pos,
	std::streampos& value)
{
	bool success = true;
	CLOG_TRACE_START_FUNCTION( );

	do
	{
		CReadFileWrapper file(m_path_to_file);
		if (!file.Initialize( ))
		{
			CLOG_ERROR("Can't initialize fstream");
			success = false;
			break;
		}

		if (!file.MoveCursorTo(start_pos))
		{
			CLOG_ERROR("Can't move curson in fstream");
			success = false;
			break;
		}

		char sym{};
		if (!file.ReadSym(sym) || sym != '{')
		{
			CLOG_ERROR("Error with reading start of JSON block");
			success = false;
			break;
		}

		size_t opened_blocks = 1;
		while (file.ReadSym(sym) && opened_blocks != 0)
		{
			if (sym == '{')
			{
				++opened_blocks;
			}
			else
				if (sym == '}')
				{
					--opened_blocks;
				}
		}

		if (opened_blocks == 0)
		{
			std::streampos end_pos = 0;
			if (!file.GetPosition(end_pos))
			{
				CLOG_ERROR("Can't get position of fstream");
				success = false;
				break;
			}
			end_pos -= 1;
			value = end_pos;
		}
	} while (false);
	CLOG_TRACE_END_FUNCTION_WITH_RETURN(success);
	return success;
}

bool CMonitoringJSONDataEntry::FindDateField(std::streampos start_pos,
	std::string& value)
{
	bool success = true;
	CLOG_TRACE_START_FUNCTION( );

	do
	{
		CReadFileWrapper file(m_path_to_file);
		if (!file.Initialize( ))
		{
			CLOG_ERROR("Can't initialize fstream");
			success = false;
			break;
		}

		if (!file.MoveCursorTo(start_pos))
		{
			CLOG_ERROR("Can't move cursor in fstream");
			success = false;
			break;
		}

		std::string str;
		while (file.ReadLine(str))
		{
			auto it = str.find("date");
			if (it != str.npos)
			{
				std::streampos date_pos = 0;
				if (!file.GetPosition(date_pos))
				{
					CLOG_ERROR("Can't get position of fstream");
					success = false;
					break;
				}

				date_pos -= str.size( );

				if (!file.MoveCursorTo(date_pos))
				{
					CLOG_ERROR("Can't move cursor in fstream");
					success = false;
					break;
				}

				if (!file.ReadLine(str))
				{
					CLOG_ERROR("Can't read line from fstream");
					success = false;
					break;
				}

				value = str;
			}
		}
	} while (false);
	CLOG_TRACE_END_FUNCTION_WITH_RETURN(success);
	return success;
}

bool CMonitoringJSONDataEntry::FormatDateFromLine(const std::string& str, 
											  time_t& value)
{
	bool success = true;
	CLOG_TRACE_START_FUNCTION( );

	do
	{
		size_t date_begin = str.find_first_of("0123456789");
		CLOG_TRACE_VAR_CREATION(date_begin);
		if (date_begin == str.npos)
		{
			CLOG_ERROR("Can't find digit symbol in line");
			success = false;
			break;
		}

		size_t date_end = str.find_last_of("0123456789") + 1;
		CLOG_TRACE_VAR_CREATION(date_end);

		if (date_end == str.npos)
		{
			CLOG_ERROR("Can't find digit symbol in line");
			success = false;
			break;
		}

		std::string date_str(str.begin( ) + date_begin, str.begin( ) + date_end);
		CLOG_TRACE_VAR_CREATION(date_str);

		if (!Utils::StringToDate(date_str, m_date_format, value))
		{
			CLOG_ERROR("Can't convert string to time_t");
			success = false;
		}
	} while (false);
	CLOG_TRACE_END_FUNCTION_WITH_RETURN(success);
	return success;
}