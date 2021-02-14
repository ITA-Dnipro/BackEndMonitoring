#pragma once

#include "CMonitoringJSONDataEntry.h"

class CMonitoringJSONDataContainer
{
public:
	CMonitoringJSONDataContainer(const std::filesystem::path& path_to_file,
							     const std::string& date_format);
	CMonitoringJSONDataContainer(const CMonitoringJSONDataContainer&) = default;
	CMonitoringJSONDataContainer(CMonitoringJSONDataContainer&&) noexcept = default;
	~CMonitoringJSONDataContainer() noexcept = default;

	bool InsertData(std::streampos block_start, std::streampos block_end,
					time_t date_time);

	bool GetAllInfo(std::string& data);
	bool GetLastInfo(std::string& data);
	bool GetSelectedInfo(time_t from, time_t to, std::string& data);

private:
	const std::filesystem::path& m_path_to_file;
	const std::string m_date_format;
	std::vector<CMonitoringJSONDataEntry> m_data_container;
};

