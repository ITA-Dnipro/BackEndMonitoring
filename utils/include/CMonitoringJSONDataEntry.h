#pragma once

class CMonitoringJSONDataEntry
{
public:
	CMonitoringJSONDataEntry(const std::filesystem::path& path_to_file,
						 std::streampos block_start, std::streampos block_end,
						 time_t date_time,const std::string& date_format);

	CMonitoringJSONDataEntry(const CMonitoringJSONDataEntry&) = default;
	CMonitoringJSONDataEntry(CMonitoringJSONDataEntry&&) noexcept = default;
	~CMonitoringJSONDataEntry() noexcept = default;
	
	bool Initialize();
	bool GetInfo(std::string& info);
	bool GetDate(time_t& date_and_time);

private:
	bool CheckData();
	bool FindEndOfJSONBlock(std::streampos, std::streampos&);
	bool FindDateField(std::streampos, std::string&);
	bool FormatDateFromLine(const std::string&, time_t&);

	std::filesystem::path m_path_to_file;
	std::streampos m_block_start;
	std::streampos m_block_end;
	const std::string m_date_format;
	time_t m_date_and_time;
};

