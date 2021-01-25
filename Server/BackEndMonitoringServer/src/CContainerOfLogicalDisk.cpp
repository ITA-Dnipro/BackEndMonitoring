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
	const unsigned short c_size_of_buffer_for_api = 1024;
	//We just skip some chars
	const unsigned short number_of_chars_need_miss = 1U;
	char container_all_disks_names[c_size_of_buffer_for_api +
		c_size_of_buffer_for_api] = {};

	if (PlatformUtils::TryGetLogicalDisksNames(container_all_disks_names,
		c_size_of_buffer_for_api))
	{
		char* variable_for_checking_names = container_all_disks_names;

		while (*variable_for_checking_names)
		{

			std::string name_of_disk = variable_for_checking_names;

			if (!Utils::TryGetFormattedDiskName(name_of_disk))
			{
				return false;
			}
			CLogicalDiskInfo* created_disk = new CLogicalDiskInfo();

			if (!created_disk->InitializeLogicalDiskStatus(
				name_of_disk, m_specification.GetCountType()))
			{
				continue;
			}

			m_p_container_all_logical_disks.push_back(created_disk);
			//go to the next driver
			variable_for_checking_names +=
				strlen(variable_for_checking_names) +
				number_of_chars_need_miss;
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
