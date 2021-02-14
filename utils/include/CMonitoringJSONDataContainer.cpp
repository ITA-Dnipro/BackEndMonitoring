#include "stdafx.h"

#include "Log.h"

#include "CMonitoringJSONDataContainer.h"

CMonitoringJSONDataContainer::CMonitoringJSONDataContainer(
	const std::filesystem::path& path_to_file, const std::string& date_format)
	: m_path_to_file(path_to_file), m_date_format(date_format)
{
	CLOG_DEBUG_START_FUNCTION( );
	CLOG_DEBUG_END_FUNCTION( );
}

bool CMonitoringJSONDataContainer::InsertData(std::streampos block_start, 
										  std::streampos block_end, 
										  time_t date_time)
{
	bool success = true;
	CLOG_DEBUG_START_FUNCTION( );
	CMonitoringJSONDataEntry temp(m_path_to_file, block_start, block_end,
							  date_time, m_date_format);
	success = temp.Initialize();
	if(success)
	{
		CLOG_TRACE("Data added to container");
		m_data_container.push_back(std::move(temp));
	}
	else
	{ 
		CLOG_WARNING("Can't add data to container");
	}
	CLOG_DEBUG_END_FUNCTION_WITH_RETURN(success);
	return success;
}

bool CMonitoringJSONDataContainer::GetAllInfo(std::string& data)
{
	CLOG_DEBUG_START_FUNCTION( );
	if (m_data_container.empty())
	{ 
		CLOG_WARNING("Data container is empty");
		return false;
	}

	std::string temp;
	for (auto entry : m_data_container)
	{
		if (entry.GetInfo(temp))
		{
			data.push_back(',');
			data.append(temp);
		} 
		else
		{
			CLOG_WARNING("Can't et data abou entry");
			return false;
		}
	}
	CLOG_DEBUG_END_FUNCTION();
	return true;
}

bool CMonitoringJSONDataContainer::GetLastInfo(std::string& data)
{
	if (!m_data_container.empty()) 
	{
		bool success = m_data_container.back( ).GetInfo(data);
		CLOG_DEBUG_VAR_CREATION(success);
		return success;
	}
	else
	{
		CLOG_WARNING("Data container is empty");
		return false;
	}
}

bool CMonitoringJSONDataContainer::GetSelectedInfo(time_t from, time_t to, 
	std::string& data)
{
	if (m_data_container.empty()) 
	{
		CLOG_WARNING("Data container is empty");
		return false;
	}

	if(to < from)
	{
		CLOG_WARNING("Date to < from");
		return false;
	}

	std::vector<std::vector<CMonitoringJSONDataEntry>::iterator> entries;
	std::vector<CMonitoringJSONDataEntry>::iterator entry;
	do
	{
		entry = std::find_if(m_data_container.begin(), m_data_container.end(),
			[from, to](CMonitoringJSONDataEntry& entry)
			{
				time_t date = 0;
				if (!entry.GetDate(date))
				{
					CLOG_WARNING("Can't get date from entry");
					return false;
				}
				return (date >= from) && (date <= to);
			});

	} while (entry != m_data_container.end());

	if(entries.size() < 0)
	{
		CLOG_WARNING("Can't find requested data");
		return false;
	}

	std::string temp;
	for(auto iter : entries)
	{ 
		if (iter->GetInfo(temp))
		{
			data.push_back(',');
			data.append(temp);
		}
		else
		{
			CLOG_WARNING("Can't get info about entry");
			return false;
		}
	}

	return true;
}


