#include "stdafx.h"

#include "Utils.h"
#include "Log.h"

#include "CResourcesInfoJSONDatabase.h"

void CResourcesInfoJSONDatabase::InsertData(long double cpu_usage,
	long double ram_usage, long double pagefile_usage)
{
	auto time = std::chrono::system_clock::now();
	
	m_data_container.push_back({std::chrono::system_clock::to_time_t(time),
		cpu_usage, ram_usage, pagefile_usage });
}

bool CResourcesInfoJSONDatabase::GetAllInfo(std::string& data)
{
	nlohmann::json temp_json;
	for (auto i : m_data_container)
	{
		temp_json.push_back({ {"date", Utils::TimeToString(i.timestamp)},
							  {"cpu", i.cpu},
							  {"ram", i.ram},
							  {"pagefile", i.pagefile} });
	}
	if (!temp_json.is_null()) {
		data.assign(temp_json.dump());
		return true;
	}
	return false;
}

bool CResourcesInfoJSONDatabase::GetLastInfo(std::string& data)
{
	if(m_data_container.empty())
	{ return false;}

	nlohmann::json temp_json;
	temp_json = { {"date", Utils::TimeToString(m_data_container.back().timestamp)},
				  {"cpu", m_data_container.back().cpu},
				  {"ram", m_data_container.back().ram},
				  {"pagefile", m_data_container.back().pagefile} };
	if (!temp_json.empty()) {
		data.assign(temp_json.dump());
		return true;
	}
	return false;
}

bool CResourcesInfoJSONDatabase::GetSelectedInfo(time_t from, time_t to, std::string& data)
{
	if (m_data_container.empty())
	{
		CLOG_WARNING("Data container is empty");
		return false;
	}

	if (to < from)
	{
		CLOG_WARNING("Date to < from");
		return false;
	}

	nlohmann::json temp_json;
	std::vector<Entry>::iterator entry;
	do
	{
		entry = std::find_if(m_data_container.begin(), m_data_container.end(),
			[from, to](const Entry& entry)
			{
				return (entry.timestamp >= from) && (entry.timestamp <= to);
			});

		if (entry != m_data_container.end())
		{
			temp_json.push_back( { {"date", Utils::TimeToString(entry->timestamp)},
								   {"cpu", entry->cpu},
								   {"ram", entry->ram},
								   {"pagefile", entry->pagefile} } );
		}
		else
		{ break;}
	} while (true);

	if(temp_json.empty())
	{ return false;}

	data.assign(temp_json.dump());
	return true;
}
