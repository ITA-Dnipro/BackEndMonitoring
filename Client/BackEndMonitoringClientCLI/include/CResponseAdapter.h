#pragma once
#include "ERequestType.h"
#include "CResponseHandler.h"

class CResponseAdapter
{
public:
	CResponseAdapter() = default;
	CResponseAdapter(const CResponseAdapter&) = delete;
	CResponseAdapter(CResponseAdapter&&) noexcept = delete;
	~CResponseAdapter() noexcept = default;

	std::string ConvertResponse(const std::string& response, 
		ERequestType request_type, bool is_table_mode);

private:
	std::string ConvertDiskInfo(const std::string& response, bool is_table_mode) const;
	std::string ConvertAllData(const std::string& response, bool is_table_mode)const;
	std::string ConvertProcessesInfo(const std::string& response, bool is_table_mode) const;
	std::string MakeDiskTable(const nlohmann::json& disk_info) const;
	std::string MakeProcTable(const nlohmann::json& proc_info) const;

	CResponseHandler m_response_handler;
};