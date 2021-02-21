#include "stdafx.h"

#include "CDataProvider.h"
#include "CJSONFormatterLogicalDisk.h"
#include "CJSONFormatterProcess.h"

CDataProvider::CDataProvider(std::shared_ptr<IInfoDatabase> p_processes_data,
							 std::shared_ptr<IInfoDatabase> p_disks_data,
	                         std::shared_ptr<IInfoDatabase> p_resources_data)
	: m_p_disks_data(p_disks_data), m_p_processes_data(p_processes_data),
	  m_p_resources_data(p_resources_data)
{ }

std::string CDataProvider::GetResourcesLoadLastInfo() const
{
	std::string resources_info;
	if (m_p_resources_data.get() == nullptr ||
		!m_p_resources_data->GetLastInfo(resources_info))
	{
		resources_info = nlohmann::json({ "error", "Can't get resources data" }).dump( );
	}
	return resources_info;
}

std::string CDataProvider::GetProcessesLastInfo() const
{
	std::string processes_info;
	if (m_p_processes_data.get() == nullptr ||
		!m_p_processes_data->GetLastInfo(processes_info))
	{
		processes_info = nlohmann::json({ "error", "Can't get processes data" }).dump();
	}
	return processes_info;
}

std::string CDataProvider::GetDisksLastInfo() const
{
	std::string disks_info;
	if (m_p_disks_data.get() == nullptr ||
		!m_p_disks_data->GetLastInfo(disks_info))
	{
		disks_info = nlohmann::json({ "error", "Can't get disks data"}).dump( );
	}
	return disks_info;
}

std::string CDataProvider::GetAllLastInfo() const
{
	nlohmann::json all_data = { {"disks info", GetDisksLastInfo()},
								{"processes info", GetProcessesLastInfo()},
								{"resources info", GetResourcesLoadLastInfo()} };

	return all_data.dump();
}



std::string CDataProvider::GetResourcesLoadFullInfo() const
{
	std::string resources_info;
	if (m_p_resources_data.get() == nullptr ||
		!m_p_resources_data->GetAllInfo(resources_info))
	{
		resources_info = nlohmann::json({"error", "Can't get resources data"}).dump( );
	}
	return resources_info;
}



std::string CDataProvider::GetProcessesFullInfo() const
{
	std::string processes_info;
	if (m_p_processes_data.get() == nullptr ||
		!m_p_processes_data->GetAllInfo(processes_info))
	{
		processes_info = nlohmann::json({ "error", "Can't get processes data"}).dump( );
	}
	return processes_info;
}

std::string CDataProvider::GetDisksFullInfo() const
{
	std::string disks_info;
	if (m_p_disks_data.get() == nullptr ||
		!m_p_disks_data->GetAllInfo(disks_info))
	{
		disks_info = nlohmann::json({ "error", "Can't get disks data"}).dump( );
	}
	return disks_info;
}

std::string CDataProvider::GetAllFullInfo() const
{
	nlohmann::json all_data = { {"disks info", GetDisksFullInfo()},
								{"processes info", GetProcessesFullInfo()},
								{"resources info", GetResourcesLoadFullInfo()} };

	return all_data.dump();
}




std::string CDataProvider::GetResourcesLoadSelectedInfo(time_t from, time_t to) const
{
	std::string resources_info;
	if (m_p_resources_data.get() == nullptr ||
		!m_p_resources_data->GetSelectedInfo(from, to, resources_info))
	{
		resources_info = nlohmann::json({"error", "Can't get resources data"}).dump( );
	}
	return resources_info;
}

std::string CDataProvider::GetProcessesSelectedInfo(time_t from, time_t to) const
{
	std::string processes_info;
	if (m_p_processes_data.get() == nullptr ||
		!m_p_processes_data->GetSelectedInfo(from, to, processes_info))
	{
		processes_info = nlohmann::json({ "error", "Can't get processes data"}).dump( );
	}
	return processes_info;
}

std::string CDataProvider::GetDisksSelectedInfo(time_t from, time_t to) const
{
	std::string disks_info;
	if (m_p_disks_data.get() == nullptr ||
		!m_p_disks_data->GetSelectedInfo(from, to, disks_info))
	{
		disks_info = nlohmann::json({ "error", "Can't get disks data" }).dump( );
	}
	return disks_info;
}

std::string CDataProvider::GetAllSelectedInfo(time_t from, time_t to) const
{
	nlohmann::json all_data = { {"disks info", GetDisksSelectedInfo(from, to)},
								{"processes info", GetProcessesSelectedInfo(from, to)},
								{"resources info", GetResourcesLoadSelectedInfo(from, to)} };

	return all_data.dump();
}
