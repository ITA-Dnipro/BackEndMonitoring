#include "stdafx.h"
#include  "GlobalVariable.h"
#include "VariadicTable.h"
#include "CResponseAdapter.h"

std::string CResponseAdapter::ConvertResponse(const std::string& response, 
	ERequestType request_type, bool is_table_mode)
{
	std::string result_str;
	try
	{
		switch (request_type)
		{
		case ERequestType::ALL_DATA:
			result_str = ConvertAllData(response, is_table_mode);
			break;
		case ERequestType::DISKS_DATA:
			result_str = ConvertDiskInfo(response, is_table_mode);
			break;
		case ERequestType::PROCESSES_DATA:
			result_str = ConvertProcessesInfo(response, is_table_mode);
			break;
		}
	}
	catch(...)
	{
		result_str = "Can not get correct response server";
	}
	
	return result_str;
}

std::string CResponseAdapter::ConvertDiskInfo(const std::string& response, 
	bool is_table_mode) const
{
	nlohmann::json json_response = nlohmann::json::parse(response);
	//nlohmann::json parsed_drives = json_response[0]["info"];

	std::string response_disk;// = json_response[0]["date"].get<std::string>();
	//response_disk += "\n";
	if(is_table_mode)
	{
		response_disk.append(MakeDiskTable(json_response));
	}
	else
	{
		response_disk.append(json_response.dump(2));
	}

	return response_disk;
}

std::string CResponseAdapter::ConvertAllData(const std::string& response, 
	bool is_table_mode) const
{
	nlohmann::json json_response = nlohmann::json::parse(response);

	std::string proc = json_response["processes info"].get<std::string>();
	nlohmann::json parsed_res = nlohmann::json::parse(proc);
	nlohmann::json parsed_proc = nlohmann::json::parse(parsed_res["processes"].get<std::string>());
	
	std::string drives = json_response["disks info"].get<std::string>();
	nlohmann::json json_drives = nlohmann::json::parse(drives);
	
	std::string converted_response;

	if(is_table_mode)
	{
		converted_response.append("\ndrives\n");
		converted_response.append(MakeDiskTable(json_drives));
		converted_response.append("\n\nprocesses\n");
		converted_response.append(MakeProcTable(parsed_proc));
	}
	else
	{
		nlohmann::json result;
		converted_response.append(nlohmann::json::parse(drives)[0]["date"].get<std::string>());
		result["processes"] = std::move(parsed_proc);
		result["drives"] = std::move(json_drives);

		converted_response.append(result.dump(2));
	}
	
	return converted_response;
}

std::string CResponseAdapter::ConvertProcessesInfo(const std::string& response, 
	bool is_table_mode) const
{
	nlohmann::json json_response = nlohmann::json::parse(response);

	nlohmann::json json_proc = json_response["processes"];
	nlohmann::json parsed_processes = nlohmann::json::parse(json_proc.get<std::string>());

	std::string converted_processes;
		
	converted_processes.append("\n");
	if(is_table_mode)
	{
		converted_processes = MakeProcTable(parsed_processes);
	}
	else
	{
		converted_processes.append(parsed_processes[0]["date"].get<std::string>());
		converted_processes.append(json_proc.get<std::string>());
	}

	return converted_processes;
}

std::string CResponseAdapter::MakeDiskTable(const nlohmann::json& disk_info) const
{
	std::string response;

	for (auto& cur_disk : disk_info)
	{
		VariadicTable<std::string, float, float, float> vt({ "Disk name", "Capacity",
"Available", "Free" }, 15);
		std::stringstream stream;
		vt.setColumnFormat({ VariadicTableColumnFormat::AUTO, VariadicTableColumnFormat::FIXED,
			VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::FIXED });
		vt.setColumnPrecision({ 0, 2, 2, 2 });
		stream << cur_disk["date"].get<std::string>();
		stream << "\n";
		for (auto& drive : cur_disk["info"])
		{
			vt.addRow(drive["name"].get<std::string>(), drive["capacity"].get<float>(),
				drive["available"].get<float>(), drive["free"].get<float>());
		}

		vt.print(stream);
		stream << "\n\n";
		response.append(stream.str());
	}

	return response;
}

std::string CResponseAdapter::MakeProcTable(const nlohmann::json& proc_info) const
{
	std::string response;

	for (auto& cur_proc : proc_info)
	{
		VariadicTable<int, float, float, float> vt({ "PID", "CPU",
	"RAM", "Pagefile" }, 15);

		std::stringstream stream;
		vt.setColumnFormat({ VariadicTableColumnFormat::AUTO, VariadicTableColumnFormat::FIXED,
			VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::FIXED });
		vt.setColumnPrecision({ 0, 2, 2, 2 });
		stream << cur_proc["date"].get<std::string>();
		stream << "\n";
		for (auto& proc : cur_proc["info"])
		{
			vt.addRow(proc["PID"].get<int>(), proc["CPU_usage"].get<float>(),
				proc["RAM_usage"].get<float>(), proc["Pagefile_usage"].get<float>());
		}
		vt.print(stream);
		stream << "\n\n";
		response.append(stream.str());
	}
	
	return response;
}