#include "stdafx.h"

#include "Utils.h"
#include "Log.h"

#include "CResourcesInfoJSONDatabase.h"

CResourcesInfoJSONDatabase::CResourcesInfoJSONDatabase()
	: m_date_format("%d.%m.%Y %X")
{ 
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_END_FUNCTION();
}

CResourcesInfoJSONDatabase::CResourcesInfoJSONDatabase(
	const std::string& date_format) : m_date_format(date_format)
{
	CLOG_DEBUG_START_FUNCTION_WITH_PARAMS(date_format);
	CLOG_DEBUG_END_FUNCTION();
}

void CResourcesInfoJSONDatabase::InsertData(long double cpu_usage,
	long double ram_usage, long double pagefile_usage)
{
	CLOG_TRACE_START_FUNCTION_WITH_PARAMS(cpu_usage, ram_usage, pagefile_usage);
	auto time = std::chrono::system_clock::now();
	CLOG_TRACE_VAR_CREATION(time);
	m_data_container.push_back({std::chrono::system_clock::to_time_t(time),
		cpu_usage, ram_usage, pagefile_usage });
	CLOG_TRACE_END_FUNCTION();
}

bool CResourcesInfoJSONDatabase::GetAllInfo(std::string& data)
{
	CLOG_DEBUG_START_FUNCTION();
	nlohmann::json temp_json;
	CLOG_TRACE_VAR_CREATION(temp_json);
	for (auto i : m_data_container)
	{
		std::string date;
		CLOG_TRACE_VAR_CREATION(date);

		if (!Utils::TimeToString(i.timestamp, date, m_date_format))
		{
			CLOG_WARNING_WITH_PARAMS("Can't convert ", i.timestamp, 
				                     "to string with format: ", m_date_format);
			return false;
		}

		temp_json.push_back({ {"date", date},
							  {"cpu", i.cpu},
							  {"ram", i.ram},
							  {"pagefile", i.pagefile} });
	}
	if (!temp_json.is_null()) {
		data.assign(temp_json.dump());
		CLOG_DEBUG("Data returned succesfully");
		return true;
	}
	CLOG_DEBUG_END_FUNCTION_WITH_RETURN(false);
	return false;
}

bool CResourcesInfoJSONDatabase::GetLastInfo(std::string& data)
{
	CLOG_DEBUG_START_FUNCTION();

	if(m_data_container.empty())
	{ 
		CLOG_WARNING("Data container is empty");
		return false;
	}
	
	std::string date;
	if(!Utils::TimeToString(m_data_container.back().timestamp, date, m_date_format))
	{
		CLOG_WARNING_WITH_PARAMS("Can't convert ", 
			                     m_data_container.back().timestamp,
			                     "to string with format: ", m_date_format);
		return false;
	}

	nlohmann::json temp_json;
	temp_json = { {"date", date},
				  {"cpu", m_data_container.back().cpu},
				  {"ram", m_data_container.back().ram},
				  {"pagefile", m_data_container.back().pagefile} };
	if (!temp_json.empty()) {
		data.assign(temp_json.dump());
		CLOG_DEBUG("Data returned succesfully");
		return true;
	}
	CLOG_DEBUG_END_FUNCTION_WITH_RETURN(false);
	return false;
}

bool CResourcesInfoJSONDatabase::GetSelectedInfo(time_t from, time_t to, std::string& data)
{
	CLOG_DEBUG_START_FUNCTION();

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
	std::vector<Entry>::iterator entry = m_data_container.begin();
	do
	{
		entry = std::find_if(entry, m_data_container.end(),
			[from, to](const Entry& entry)
			{
				return (entry.timestamp >= from) && (entry.timestamp <= to);
			});

		if (entry != m_data_container.end())
		{
			std::string date;
			if (!Utils::TimeToString(entry->timestamp, date, m_date_format))
			{ 
				CLOG_WARNING_WITH_PARAMS("Can't convert ", entry->timestamp,
					                     "to string with format: ", m_date_format);
				continue;
			}

			temp_json.push_back( { {"date", date},
								   {"cpu", entry->cpu},
								   {"ram", entry->ram},
								   {"pagefile", entry->pagefile} } );

			++entry;
		}
		else
		{ break;}
	} while (true);

	if(temp_json.empty())
	{ 
		CLOG_WARNING("No data in asked range");
		return false;
	}

	data.assign(temp_json.dump());
	CLOG_DEBUG_END_FUNCTION_WITH_RETURN(true);
	return true;
}
