#include "stdafx.h"

#include "CMonitoringJSONDataContainer.h"

CMonitoringJSONDataContainer::CMonitoringJSONDataContainer(
	const std::filesystem::path& path_to_file, const std::string& date_format)
	: m_path_to_file(path_to_file), m_date_format(date_format)
{ }

bool CMonitoringJSONDataContainer::InsertData(std::streampos block_start, 
										  std::streampos block_end, 
										  time_t date_time)
{
	CMonitoringJSONDataEntry temp(m_path_to_file, block_start, block_end,
							  date_time, m_date_format);
	bool success = temp.Initialize();
	if(success)
	{ m_data_container.push_back(std::move(temp));}
	return success;
}

bool CMonitoringJSONDataContainer::GetAllInfo(std::string& data)
{
	if (m_data_container.empty())
	{ return false; }

	std::string temp;
	for (auto entry : m_data_container)
	{
		if (entry.GetInfo(temp))
		{
			data.push_back(',');
			data.append(temp);
		} 
		else
		{ return false;}
	}
	return true;
}

bool CMonitoringJSONDataContainer::GetLastInfo(std::string& data)
{
	if (!m_data_container.empty()) 
	{
		return  m_data_container.back().GetInfo(data);
	}
	return false;
}

bool CMonitoringJSONDataContainer::GetSelectedInfo(time_t from, time_t to, 
	std::string& data)
{
	if (m_data_container.empty()) 
	{ return false;}

	if(to < from)
	{ return false;}

	std::vector<std::vector<CMonitoringJSONDataEntry>::iterator> entries;
	std::vector<CMonitoringJSONDataEntry>::iterator entry;
	do
	{
		entry = std::find_if(m_data_container.begin(), m_data_container.end(),
			[from, to](CMonitoringJSONDataEntry& entry)
			{
				time_t date = 0;
				if (!entry.GetDate(date))
				{ return false;}
				return (date >= from) && (date <= to);
			});

	} while (entry != m_data_container.end());

	if(entries.size() > 0)
	{ return true;}

	std::string temp;
	for(auto iter : entries)
	{ 
		if (iter->GetInfo(temp))
		{
			data.push_back(',');
			data.append(temp);
		}
		else
		{ return false;}
	}

	return true;
}


