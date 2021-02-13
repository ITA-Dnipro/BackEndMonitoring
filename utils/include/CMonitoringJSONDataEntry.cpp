#include "stdafx.h"

#include "Utils.h"
#include "CReadFileWrapper.h"

#include "CMonitoringJSONDataEntry.h"

CMonitoringJSONDataEntry::CMonitoringJSONDataEntry(
	const std::filesystem::path& path_to_file, 
	std::streampos block_start, std::streampos block_end,
	time_t date_time,const std::string& date_format)
	: m_path_to_file(path_to_file), m_block_start(block_start),
	  m_block_end(block_end), m_date_and_time(date_time),
	  m_date_format(date_format)
	  
{ }

bool CMonitoringJSONDataEntry::Initialize()
{
	return CheckData();
}

bool CMonitoringJSONDataEntry::GetInfo(std::string& info)
{
	if(!CheckData())
	{ return false;}

	CReadFileWrapper file(m_path_to_file);
	if(!file.Initialize())
	{ return false;}
	
	if(!file.MoveCursorTo(m_block_start))
	{ return false;}

	if(!file.Read(info, m_block_end-m_block_start))
	{ return false;}

	return true;
}

bool CMonitoringJSONDataEntry::GetDate(time_t& date_and_time)
{
	if(!CheckData())
	{ return false;}

	date_and_time = m_date_and_time;
	return true;
}

bool CMonitoringJSONDataEntry::CheckData()
{
	std::string date_str;
	if(!FindDateField(m_block_start, date_str))
	{ return false;}

	time_t date;
	if(!FormatDateFromLine(date_str, date))
	{ return false;}
	if(!(date == m_date_and_time))
	{ return false;}

	std::streampos end_of_block;
	if(!FindEndOfJSONBlock(m_block_start, end_of_block))
	{ return false;}
	if(!(m_block_end == end_of_block))
	{ return false;}

	return true;
}

bool CMonitoringJSONDataEntry::FindEndOfJSONBlock(std::streampos start_pos,
	std::streampos& value)
{
	CReadFileWrapper file(m_path_to_file);
	if(!file.Initialize())
	{ return false;}

	if(!file.MoveCursorTo(start_pos))
	{ return false;}

	char sym{};
	if (!file.ReadSym(sym) || sym != '{')
	{ return false;}

	size_t opened_blocks = 1;
	while (file.ReadSym(sym) && opened_blocks != 0)
	{
		if (sym == '{')
		{ ++opened_blocks;}
		else
		if (sym == '}')
		{ --opened_blocks;}
	}

	if (opened_blocks == 0)
	{
		std::streampos end_pos = 0;
		if (!file.GetPosition(end_pos))
		{ return false;}
		end_pos -= 1;
		value = end_pos;
		return true;
	}
	return false;
}

bool CMonitoringJSONDataEntry::FindDateField(std::streampos start_pos,
	std::string& value)
{
	CReadFileWrapper file(m_path_to_file);
	if(!file.Initialize())
	{ return false;}

	if(!file.MoveCursorTo(start_pos))
	{ return false;}

	std::string str;
	while (file.ReadLine(str))
	{
		auto it = str.find("date");
		if (it != str.npos)
		{
			std::streampos date_pos = 0;
			if (!file.GetPosition(date_pos))
			{ return false;}

			date_pos -= str.size();
			
			if (!file.MoveCursorTo(date_pos))
			{ return false;}

			if (!file.ReadLine(str))
			{ return false;}

			value = str;
			return true;
		}
	}
	return false;
}

bool CMonitoringJSONDataEntry::FormatDateFromLine(const std::string& str, 
											  time_t& value)
{
	size_t date_begin = str.find_first_of("0123456789");
	if (date_begin == str.npos)
	{ return false;}

	size_t date_end = str.find_last_of("0123456789") + 1;
	if (date_end == str.npos)
	{ return false;}

	std::string date_str(str.begin() + date_begin, str.begin() + date_end);

	return Utils::StringToDate(date_str, m_date_format, value);
}