#include "stdafx.h"

#include "CDataProvider.h"
#include "CJSONFormatterLogicalDisk.h"
#include "CJSONFormatterProcess.h"

CDataProvider::CDataProvider(std::shared_ptr<IInfoDatabase> p_processes_data,
							 std::shared_ptr<IInfoDatabase> p_disks_data)
	: m_p_disks_data(p_disks_data), m_p_processes_data(p_processes_data)
{ }

std::string CDataProvider::GetProcessesInfo( ) const
{
	std::string processes_info;
	if (m_p_processes_data.get() == nullptr ||
		!m_p_processes_data->GetAllInfo(processes_info))
	{
		processes_info = "Can't get processes data";
	}
	return processes_info;
}


std::string CDataProvider::GetDisksInfo( ) const
{
	std::string disks_info;
	if (m_p_disks_data.get( ) == nullptr || 
		!m_p_disks_data->GetAllInfo(disks_info))
	{
		disks_info = "Can't get disks data";
	}
	return disks_info;
}

std::string CDataProvider::GetAllInfo( ) const
{
	nlohmann::json all_data = { {"disks info", GetDisksInfo()},
								{"processes info", GetProcessesInfo()} };

	return all_data.dump( );
}
