#include "stdafx.h"

#include "CLogicalDiskInfo.h"
#include "CJSONFormatterLogicalDisk.h"
#include "Utils.h"

#include "CDrivesInfoJSONDatabase.h"

CDrivesInfoJSONDatabase::CDrivesInfoJSONDatabase(
	std::filesystem::path path_to_file)
	: CMonitoringInfoJSONDatabase(path_to_file)
{ }

CDrivesInfoJSONDatabase::CDrivesInfoJSONDatabase(
	std::filesystem::path path_to_file,
	const std::string& date_format)
	: CMonitoringInfoJSONDatabase(path_to_file, date_format)
{ }

bool CDrivesInfoJSONDatabase::CommitDataAdd(const CLogicalDiskInfo & data_to_json,
											unsigned short disk_number)
{
    return m_json_formatter.TryAddLogicalDiskData(data_to_json, disk_number);
}

bool CDrivesInfoJSONDatabase::ClearCommitedData( )
{
    return m_json_formatter.TryEraseAllData( );
}

bool CDrivesInfoJSONDatabase::InsertCommitedData( )
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
