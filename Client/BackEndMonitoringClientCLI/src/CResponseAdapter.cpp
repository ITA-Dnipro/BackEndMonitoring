#include "stdafx.h"
#include "CResponseAdapter.h"
#include  "GlobalVariable.h"

std::string CResponseAdapter::ConvertResponse(const std::string& response, 
	ERequestType request_type, bool is_table_mode) const
{
	std::string result_str;
	try
	{
		switch (request_type)
		{
		case ERequestType::ALL_DATA:
			result_str = ConvertAllData(response);
			break;
		case ERequestType::DISKS_DATA:
			result_str = ConvertDiskInfo(response);
			break;
		case ERequestType::PROCESSES_DATA:
			result_str = ConvertProcessesInfo(response);
			break;
		}
	}
	catch(...)
	{
		result_str = "Cannot parse response from the server";
	}
	
	return result_str;
}

std::string CResponseAdapter::ConvertDiskInfo(const std::string& response) const
{
	nlohmann::json json_response = nlohmann::json::parse(response);
	nlohmann::json parsed_drives = json_response[0]["info"];
	
	return json_response[0]["info"].dump(2);
}

std::string CResponseAdapter::ConvertAllData(const std::string& response) const
{
	nlohmann::json json_response = nlohmann::json::parse(response);

	std::string proc = json_response["processes info"].get<std::string>();
	nlohmann::json parsed_res = nlohmann::json::parse(proc);
	nlohmann::json parsed_proc = nlohmann::json::parse(parsed_res["processes"].get<std::string>());
	nlohmann::json parsed_proc2 = nlohmann::json::parse(parsed_res["resources"].get<std::string>());
	
	std::string drives = json_response["disks info"].get<std::string>();
	nlohmann::json parsed_drives = nlohmann::json::parse(drives);
	
	nlohmann::json result;
	result["resources"] = std::move(parsed_proc);
	result["processes"] = std::move(parsed_proc2);
	result["drives"] = std::move(parsed_drives);
	
	return result.dump(2);
}

std::string CResponseAdapter::ConvertProcessesInfo(const std::string& response) const
{
	nlohmann::json json_response = nlohmann::json::parse(response);

	std::string parsed_processes;
	parsed_processes.append(json_response["processes"].get<std::string>());

	return parsed_processes;
}
