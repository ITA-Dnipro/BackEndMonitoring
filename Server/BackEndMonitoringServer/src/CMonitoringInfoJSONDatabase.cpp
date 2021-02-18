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
{
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_END_FUNCTION( );
}

CMonitoringInfoJSONDatabase::CMonitoringInfoJSONDatabase(
	std::filesystem::path path_to_file, const std::string& date_format)
	: m_path_to_file(path_to_file), m_saver(m_path_to_file), 
	  m_date_format(date_format), m_reader(m_path_to_file, m_date_format),
	  m_p_path_constructor(new CDateTimePathConstructor(m_path_to_file.string( )))
{
	CLOG_DEBUG_START_FUNCTION( );
	CLOG_DEBUG_END_FUNCTION( );
}

bool CMonitoringInfoJSONDatabase::GetAllInfo(std::string& data)
{
	CLOG_DEBUG_START_FUNCTION( );
	std::lock_guard<std::mutex> guard(m_lock);
	CLOG_TRACE("Obtained data mutex");
	CLOG_DEBUG_END_FUNCTION( );
	return m_reader.GetAllInfo(data);

}

bool CMonitoringInfoJSONDatabase::GetLastInfo(std::string& data)
{
	CLOG_DEBUG_START_FUNCTION( );
	std::lock_guard<std::mutex> guard(m_lock);
	CLOG_TRACE("Obtained data mutex");
	CLOG_DEBUG_END_FUNCTION( );
	return m_reader.GetLastInfo(data);
}

bool CMonitoringInfoJSONDatabase::GetSelectedInfo(time_t from, time_t to, std::string& data)
{
	CLOG_DEBUG_START_FUNCTION( );
	std::lock_guard<std::mutex> guard(m_lock);
	CLOG_TRACE("Obtained data mutex");
	CLOG_DEBUG_END_FUNCTION( );
	return m_reader.GetSelectedInfo(from, to, data);
}
