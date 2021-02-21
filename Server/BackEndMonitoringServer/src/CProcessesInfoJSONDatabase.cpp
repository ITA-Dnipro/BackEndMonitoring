#include "stdafx.h"

#include "Utils.h"
#include "CDateTimePathConstructor.h"
#include "Log.h"

#include "CProcessesInfoJSONDatabase.h"

CProcessesInfoJSONDatabase::CProcessesInfoJSONDatabase(
	const std::filesystem::path& path_to_file)
	: CMonitoringInfoJSONDatabase(path_to_file)
{ }

CProcessesInfoJSONDatabase::CProcessesInfoJSONDatabase(
	const std::filesystem::path& path_to_file, const std::string& date_format)
	: CMonitoringInfoJSONDatabase(path_to_file, date_format)
{ }

bool CProcessesInfoJSONDatabase::CommitDataAdd(const CProcessInfo & data_to_json)
{
	bool success = true;
	CLOG_DEBUG_START_FUNCTION( );
	success = m_json_formatter.TryAddProcessData(data_to_json);
	CLOG_DEBUG_END_FUNCTION_WITH_RETURN(success);
	return success;
}

bool CProcessesInfoJSONDatabase::ClearCommitedData()
{
	bool success = true;
	CLOG_DEBUG_START_FUNCTION( );
	success = m_json_formatter.TryEraseAllData( );
	CLOG_DEBUG_END_FUNCTION_WITH_RETURN(success);
	return success;
}

bool CProcessesInfoJSONDatabase::InsertCommitedData()
{
	bool success = true;
	CLOG_DEBUG_START_FUNCTION( );
	std::streampos begin;
	std::streampos end;

	auto json = m_json_formatter.GetJSONFormattedData( );
	CLOG_TRACE_VAR_CREATION(json);
	auto date_iter = json->back( ).find("date");
	CLOG_TRACE_VAR_CREATION(date_iter);

	do
	{
		if (json->back( ).end( ) == date_iter)
		{
			CLOG_ERROR("Failed to find date in json block");
			break;
		}
		if (!date_iter.value( ).is_string( ))
		{
			CLOG_ERROR("Invalid date in json block");
			break;
		}
		std::string date_str = *date_iter;
		time_t date;
		if (!Utils::StringToDate(date_str, m_date_format, date))
		{
			CLOG_ERROR("Failed to convert date");
			break;
		}

		std::lock_guard<std::mutex> guard(m_lock);
		std::string new_path = m_path_to_file.string( );
		if (!m_p_path_constructor->UpdatePathToFile(new_path))
		{
			CLOG_ERROR_WITH_PARAMS("Failed to update path", new_path);
			break;
		}

		m_path_to_file = new_path;
		if (!m_saver.TrySaveToFile(m_json_formatter, begin, end))
		{
			CLOG_ERROR("Failed to save to file");
			break;
		}
		if (!m_reader.InsertData(begin, end, date))
		{
			CLOG_ERROR("Failed to insert data into database");
			break;
		}
		success = true;
	} while (false);

	CLOG_DEBUG_END_FUNCTION_WITH_RETURN(success);
	return success;
}
