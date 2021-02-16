#pragma once

#include "IInfoDatabase.h"

class CResourcesInfoJSONDatabase : public IInfoDatabase
{ 
public:
	CResourcesInfoJSONDatabase( ) = default;
	CResourcesInfoJSONDatabase(const CResourcesInfoJSONDatabase&) = default;
	CResourcesInfoJSONDatabase(CResourcesInfoJSONDatabase&&) noexcept = default;

	~CResourcesInfoJSONDatabase() noexcept = default;

	void InsertData(long double cpu_usage,
		long double ram_usage, long double pagefile_usage);

	bool GetAllInfo(std::string& data) override;
	bool GetLastInfo(std::string& data) override;
	bool GetSelectedInfo(time_t from, time_t to, std::string& data) override;
private:
	struct Entry
	{
		time_t timestamp;
		long double cpu;
		long double ram;
		long double pagefile;
	};

	std::vector<Entry> m_data_container;
};