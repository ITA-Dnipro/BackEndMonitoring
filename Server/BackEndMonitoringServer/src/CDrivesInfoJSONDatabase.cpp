#include "stdafx.h"

#include "CLogicalDiskInfo.h"
#include "CJSONFormatterLogicalDisk.h"
#include "CDateTimePathConstructor.h"
#include "Utils.h"
#include "Log.h"

#include "CDrivesInfoJSONDatabase.h"

CDrivesInfoJSONDatabase::CDrivesInfoJSONDatabase(
	const std::filesystem::path& path_to_file)
	: CMonitoringInfoJSONDatabase(path_to_file)
{
	CLOG_DEBUG_START_FUNCTION( );
	CLOG_DEBUG_END_FUNCTION( );
}

CDrivesInfoJSONDatabase::CDrivesInfoJSONDatabase(
	const std::filesystem::path& path_to_file,
	const std::string& date_format)
	: CMonitoringInfoJSONDatabase(path_to_file, date_format)
{
	CLOG_DEBUG_START_FUNCTION( );
	CLOG_DEBUG_END_FUNCTION( );
}

bool CDrivesInfoJSONDatabase::CommitDataAdd(const CLogicalDiskInfo & data_to_json)
{
	bool success = true;
	CLOG_DEBUG_START_FUNCTION( );
	success = m_json_formatter.TryAddLogicalDiskData(data_to_json);
	CLOG_DEBUG_END_FUNCTION_WITH_RETURN(success);
	return success;
}

bool CDrivesInfoJSONDatabase::ClearCommitedData( )
{
	bool success = true;
	CLOG_DEBUG_START_FUNCTION( );
	success = m_json_formatter.TryEraseAllData( );
	CLOG_DEBUG_END_FUNCTION_WITH_RETURN(success);
	return success;
}

bool CDrivesInfoJSONDatabase::InsertCommitedData( )
{
	bool success = true;
	CLOG_DEBUG_START_FUNCTION( );
	std::streampos begin;
	CLOG_TRACE_VAR_CREATION(begin);
	std::streampos end;
	CLOG_TRACE_VAR_CREATION(end);

	auto json = m_json_formatter.GetJSONFormattedData( );
	CLOG_TRACE_VAR_CREATION(json);
	auto date_iter = json->back().find("date");
	CLOG_TRACE_VAR_CREATION(date_iter);

	do
	{
		if (date_iter == json->back( ).end( ))
		{
			CLOG_ERROR("Cant find date in json block");
			success = false;
			break;
		}
		if (!date_iter.value( ).is_string( ))
		{
			CLOG_ERROR("Cant find date in json block");
			success = false;
			break;
		}
		std::string date_str = *date_iter;
		time_t date;
		if (!Utils::StringToDate(date_str, m_date_format, date))
		{
			CLOG_ERROR("Cant convert string to time_t");
			success = false;
			break;
		}

		std::lock_guard<std::mutex> guard(m_lock);
		std::string new_path = m_path_to_file.string( );
		if (!m_p_path_constructor->UpdatePathToFile(new_path))
		{
			CLOG_ERROR("Cant update path to file");
			success = false;
			break;
		}

		m_path_to_file = new_path;
		if (!m_saver.TrySaveToFile(m_json_formatter, begin, end))
		{
			CLOG_ERROR("Cant save to file");
			success = false;
			break;
		}
		if (!m_reader.InsertData(begin, end, date))
		{
			CLOG_ERROR("Cant insert data into database");
			success = false;
			break;
		}
	} while (false);

	CLOG_DEBUG_END_FUNCTION_WITH_RETURN(success);
	return success;
}
