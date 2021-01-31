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
	nlohmann::json all_data = { {"disks info", *disks_data.GetJSONFormattedData()},
							    {"processes info", *processes_data.GetJSONFormattedData()} };

	return all_data.dump( );
}