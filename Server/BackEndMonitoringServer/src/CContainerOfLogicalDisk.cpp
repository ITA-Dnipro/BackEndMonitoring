#include "stdafx.h"

#include "Utils.h"
#include "PlatformUtils.h"
#include "CLogicalDiskInfo.h"
#include "CContainerOfLogicalDisk.h"
#include "CJSONFormatterLogicalDisk.h"
#include "CLogger/include/Log.h"


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
	CLOG_DEBUG_START_FUNCTION();
	for (const auto& disk : m_p_container_all_logical_disks)
	{
		if (nullptr != disk)
		{
			delete disk;
		}
	}
	CLOG_DEBUG_END_FUNCTION();
}

bool CContainerOfLogicalDisk::TryGetAllExistedLogicalDisksAndInfo()
{
	CLOG_DEBUG_START_FUNCTION();
	if (!IsInitialized())
	{
		// will be changed after implementing an exception handler
		CLOG_PROD(
			"ERROR!!! Call function on uninitialized container of disks");
		return false;
	}
	std::vector<std::string> all_names_of_disks;
	CLOG_TRACE_VAR_CREATION(all_names_of_disks);

	if (PlatformUtils::TryGetLogicalDisksNames(all_names_of_disks))
	{
		for (const auto& disk_name : all_names_of_disks)
		{
			CLogicalDiskInfo* created_disk = new CLogicalDiskInfo();
			CLOG_TRACE_VAR_CREATION(created_disk);
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

	CLOG_DEBUG_END_FUNCTION();
	return true;
}

bool CContainerOfLogicalDisk::InitializeContainerOfLogicalDisk()
{
	CLOG_DEBUG_START_FUNCTION();
	m_is_initialized = true;

	if (!TryGetAllExistedLogicalDisksAndInfo())
	{
		m_is_initialized = false;
		return false;
	}
	CLOG_DEBUG_END_FUNCTION();
	return true;
}

bool CContainerOfLogicalDisk::IsInitialized() const
{
	return m_is_initialized;
}

bool CContainerOfLogicalDisk::TryUpdateInfoLogicalDiskToJSON(
	CJSONFormatterLogicalDisk& json_formatter)
{
	CLOG_DEBUG_START_FUNCTION();
	unsigned short disk_number = 0;
	CLOG_TRACE_VAR_CREATION(disk_number);
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
	CLOG_DEBUG_END_FUNCTION();
	return true;
}

const std::vector<CLogicalDiskInfo*>* CContainerOfLogicalDisk::GetAllLogicalDisk() const
{
	CLOG_DEBUG_START_FUNCTION();
	if (!IsInitialized())
	{
		// will be changed after implementing an exception handler
		return nullptr;
	}
	CLOG_DEBUG_END_FUNCTION();
	return &m_p_container_all_logical_disks;
}

const CHardwareStatusSpecification* CContainerOfLogicalDisk::GetSpecification() const
{
	return &m_specification;
}
