#include "stdafx.h"

#include "Utils.h"

#include "CMonitoringInfoJSONDatabase.h"

CMonitoringInfoJSONDatabase::CMonitoringInfoJSONDatabase(
	std::filesystem::path path_to_file)
	: m_saver(path_to_file.string()), m_reader(path_to_file, m_date_format), 
	  m_date_format("%d.%m.%Y %X")
{ }

CMonitoringInfoJSONDatabase::CMonitoringInfoJSONDatabase(
	std::filesystem::path path_to_file, const std::string& date_format)
	: m_saver(path_to_file.string( )), m_reader(path_to_file, m_date_format),
	m_date_format(date_format)
{ }

bool CMonitoringInfoJSONDatabase::GetAllInfo(std::string& data)
{
	std::lock_guard<std::mutex> guard(m_lock);
	return m_reader.GetAllInfo(data);
}

bool CMonitoringInfoJSONDatabase::GetLastInfo(std::string& data)
{
	std::lock_guard<std::mutex> guard(m_lock);
	return m_reader.GetLastInfo(data);
}

bool CMonitoringInfoJSONDatabase::GetSelectedInfo(time_t from, time_t to, std::string& data)
{
	std::lock_guard<std::mutex> guard(m_lock);
	return m_reader.GetSelectedInfo(from, to, data);
}
