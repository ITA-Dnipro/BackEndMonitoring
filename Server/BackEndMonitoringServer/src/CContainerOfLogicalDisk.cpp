#include "stdafx.h"

#include "Utils.h"
#include "PlatformUtils.h"
#include "CLogicalDiskInfo.h"
#include "CContainerOfLogicalDisk.h"
#include "CJSONFormatterLogicalDisk.h"

CContainerOfLogicalDisk::CContainerOfLogicalDisk(
	std::chrono::duration<int> period_of_checking_status,
	const std::string& path_to_file,
	EMemoryConvertType count_type) :
	m_specification(period_of_checking_status,
		path_to_file,
		count_type),
	m_is_initialized(false)
{};

CContainerOfLogicalDisk::CContainerOfLogicalDisk(
	const CHardwareStatusSpecification& orig) :
	m_specification(orig), m_is_initialized(false)
{};

CContainerOfLogicalDisk::CContainerOfLogicalDisk(
	const CContainerOfLogicalDisk& orig) :
	m_specification(orig.m_specification),
	m_p_container_all_logical_disks(orig.m_p_container_all_logical_disks),
	m_is_initialized(orig.m_is_initialized)
{};

CContainerOfLogicalDisk::~CContainerOfLogicalDisk() noexcept
{
	for (const auto& disk : m_p_container_all_logical_disks)
	{
		delete disk;
	}
}

bool CContainerOfLogicalDisk::TryGetAllExistedLogicalDisksAndInfo()
{
	if (!IsInitialized())
	{
		// will be changed after implementing an exception handler
		return false;
	}
	std::vector<std::string> all_names_of_disks;

	if (PlatformUtils::TryGetLogicalDisksNames(all_names_of_disks))
	{
		for (const auto& disk_name : all_names_of_disks)
		{
			CLogicalDiskInfo* created_disk = new CLogicalDiskInfo();

			//avoid floppy disk or another logical disk without capacity
			if (created_disk->InitializeLogicalDiskStatus(
				disk_name, m_specification.GetCountType()))
			{
				m_p_container_all_logical_disks.push_back(created_disk);
			}

		}
	}
	else
	{
		return false;
	}

	return true;
}

bool CContainerOfLogicalDisk::InitializeContainerOfLogicalDisk()
{
	m_is_initialized = true;

	if (!TryGetAllExistedLogicalDisksAndInfo())
	{
		m_is_initialized = false;
		return false;
	}

	return true;
}

bool CContainerOfLogicalDisk::IsInitialized() const
{
	return m_is_initialized;
}

bool CContainerOfLogicalDisk::TryUpdateInfoLogicalDiskToJSON(
	CJSONFormatterLogicalDisk& json_formatter)
{
	unsigned short disk_number = 0;

	for (const auto& disk : m_p_container_all_logical_disks)
	{

		if (!disk->TryUpdateCurrentStatus())
		{
			// exception
			std::cout << "Enable to update!" << std::endl;
			return false;
		}
		if (!json_formatter.TryAddLogicalDiskData(*disk, disk_number))
		{
			//exception handler
			continue;
		}
		disk_number++;
	}
	return true;
}

const std::vector<CLogicalDiskInfo*>* CContainerOfLogicalDisk::GetAllLogicalDisk() const
{
	if (!IsInitialized())
	{
		// will be changed after implementing an exception handler
		return nullptr;
	}
	return &m_p_container_all_logical_disks;
}

const CHardwareStatusSpecification* CContainerOfLogicalDisk::GetSpecification() const
{
	return &m_specification;
}
