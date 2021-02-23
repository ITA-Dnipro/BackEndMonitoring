#pragma once
#include "ERequestType.h"

class CResponseAdapter
{
public:
	CResponseAdapter() = default;
	CResponseAdapter(const CResponseAdapter&) = delete;
	CResponseAdapter(CResponseAdapter&&) noexcept = delete;
	~CResponseAdapter() noexcept = default;

	std::string ConvertResponse(const std::string& response, 
		ERequestType request_type, bool is_table_mode) const;

private:
	std::string ConvertDiskInfo(const std::string& response) const;
	std::string ConvertAllData(const std::string& response)const;
	std::string ConvertProcessesInfo(const std::string& response) const;


};