#include "IInfoDatabase.h"

class CResourcesInfoJSONDatabase : public IInfoDatabase
{ 
public:
	CResourcesInfoJSONDatabase( ) = default;
	CResourcesInfoJSONDatabase(const CResourcesInfoJSONDatabase&) = default;
	CResourcesInfoJSONDatabase(CResourcesInfoJSONDatabase&&) noexcept = default;

	~CResourcesInfoJSONDatabase() noexcept = default;

	bool InsertData(double cpu_usage, double ram_usage, double pagefile_usage);

	bool GetAllInfo(std::string& data) override;
	bool GetLastInfo(std::string& data) override;
	bool GetSelectedInfo(time_t from, time_t to, std::string& data) override;
private:
	struct Entry
	{
		double cpu;
		double ram;
		double pagefile;
	};

	std::vector<Entry> m_data_container;
};