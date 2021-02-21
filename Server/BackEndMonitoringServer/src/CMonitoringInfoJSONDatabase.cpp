#include "stdafx.h"

#include "Utils.h"
#include "CDateTimePathConstructor.h"
#include "Log.h"

#include "CMonitoringInfoJSONDatabase.h"

CMonitoringInfoJSONDatabase::CMonitoringInfoJSONDatabase(
	std::filesystem::path path_to_file)
	: m_path_to_file(path_to_file), m_saver(m_path_to_file),
	  m_date_format("%d.%m.%Y %X"), 
	  m_reader(m_path_to_file, m_date_format),
	  m_p_path_constructor(new CDateTimePathConstructor(m_path_to_file.string( )))
{ }

CMonitoringInfoJSONDatabase::CMonitoringInfoJSONDatabase(
	std::filesystem::path path_to_file, const std::string& date_format)
	: m_path_to_file(path_to_file), m_saver(m_path_to_file), 
	  m_date_format(date_format), m_reader(m_path_to_file, m_date_format),
	  m_p_path_constructor(new CDateTimePathConstructor(m_path_to_file.string( )))
{ }

bool CMonitoringInfoJSONDatabase::GetAllInfo(std::string& data)
{
	bool success = false;
	CLOG_DEBUG_START_FUNCTION( );
	std::lock_guard<std::mutex> guard(m_lock);
	CLOG_TRACE("Obtained data mutex");
	success = m_reader.GetAllInfo(data);
	CLOG_DEBUG_END_FUNCTION_WITH_RETURN(success);
	return success;
}

bool CMonitoringInfoJSONDatabase::GetLastInfo(std::string& data)
{
	bool success = false;
	CLOG_DEBUG_START_FUNCTION( );
	std::lock_guard<std::mutex> guard(m_lock);
	CLOG_TRACE("Obtained data mutex");
	success = m_reader.GetLastInfo(data);
	CLOG_DEBUG_END_FUNCTION_WITH_RETURN(success);
	return success;
}

bool CMonitoringInfoJSONDatabase::GetSelectedInfo(time_t from, time_t to, std::string& data)
{
	bool success = false;
	CLOG_DEBUG_START_FUNCTION( );
	std::lock_guard<std::mutex> guard(m_lock);
	CLOG_TRACE("Obtained data mutex");
	success = m_reader.GetSelectedInfo(from, to, data);
	CLOG_DEBUG_END_FUNCTION_WITH_RETURN(success);
	return success;
}
