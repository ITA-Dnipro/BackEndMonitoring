#include "stdafx.h"

#include "Utils.h"

#include "CProcessesInfoJSONDatabase.h"

CProcessesInfoJSONDatabase::CProcessesInfoJSONDatabase(
	std::filesystem::path path_to_file)
	: CMonitoringInfoJSONDatabase(path_to_file)
{ }

CProcessesInfoJSONDatabase::CProcessesInfoJSONDatabase(
	std::filesystem::path path_to_file, const std::string& date_format)
	: CMonitoringInfoJSONDatabase(path_to_file, date_format)
{ }

bool CProcessesInfoJSONDatabase::CommitDataAdd(const CProcessInfo & data_to_json)
{
	return m_json_formatter.TryAddProcessData(data_to_json);
}

bool CProcessesInfoJSONDatabase::ClearCommitedData()
{
	return m_json_formatter.TryEraseAllData( );
}

bool CProcessesInfoJSONDatabase::InsertCommitedData()
{
	std::streampos begin;
	std::streampos end;

	auto json = m_json_formatter.GetJSONFormattedData( );
	auto date_iter = json->find("date");
	if (date_iter == json->end( ))
	{
		return false;
	}
	if (!date_iter.value( ).is_string( ))
	{
		return false;
	}
	std::string date_str = *date_iter;
	time_t date;
	if (!Utils::StringToDate(date_str, m_date_format, date))
	{
		return false;
	}

	std::lock_guard<std::mutex> guard(m_lock);
	if (!m_saver.TrySaveToFile(m_json_formatter, begin, end))
	{
		return false;
	}
	if (!m_reader.InsertData(begin, end, date))
	{
		return false;
	}

	return true;
}
