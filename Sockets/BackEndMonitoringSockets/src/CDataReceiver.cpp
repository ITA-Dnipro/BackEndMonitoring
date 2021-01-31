#include "stdafx.h"

#include "CDataReceiver.h"
#include "Server/BackEndMonitoringServer/include/CJSONFormatterLogicalDisk.h"
#include "Server/BackEndMonitoringServer/include/CJSONFormatterProcess.h"

CDataReceiver::CDataReceiver(CThreadSafeVariable<CJSONFormatterProcess>& processes_json,
							 CThreadSafeVariable<CJSONFormatterLogicalDisk>& disks_json)
	: m_disks_json(disks_json), m_processes_json(processes_json)
{ }

std::string CDataReceiver::GetProcessesInfo( )
{
	std::string processes_info;
	{
		auto [data, mtx] = m_processes_json.GetAccess( );
		if (!data.TryGetJSONDataAsString(processes_info))
		{
			processes_info = "Can't get processes data";
		}
	}
	return processes_info;
}


std::string CDataReceiver::GetDisksInfo( )
{
	std::string disks_info;
	{
		auto [data, mtx] = m_disks_json.GetAccess( );
		if (!data.TryGetJSONDataAsString(disks_info))
		{
			disks_info = "Can't get disks data";
		}
	}
	return disks_info;
}

std::string CDataReceiver::GetAllInfo( )
{
	auto [disks_data, disks_mtx] = m_disks_json.GetAccess( );
	auto [processes_data, processes_mtx] = m_processes_json.GetAccess( );
	nlohmann::json* disks_json = disks_data.GetJSONFormattedData();
	if (disks_json == nullptr)
	{
		disks_json = new nlohmann::json("Can't get disks data");
	}

	nlohmann::json* processes_json = processes_data.GetJSONFormattedData();
	if (processes_json == nullptr)
	{
		processes_json = new nlohmann::json("Can't get processes data");
	}

	nlohmann::json all_data = { {"disks info", *disks_json},
								{"processes info", *processes_json} };
	delete processes_json;
	delete disks_json;

	return all_data.dump( );
}