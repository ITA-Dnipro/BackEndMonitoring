#include "stdafx.h"

#include "Utils.h"
#include "CLogicalDiskStatus.h"
#include "CContainerOfLogicalDisk.h"

CContainerOfLogicalDisk::CContainerOfLogicalDisk(
	std::chrono::duration<int> period_of_checking_status,
	const std::string& path_to_file,
	EMemoryCountType count_type) :
	CHardwareStatusSpecification(period_of_checking_status,
		path_to_file,
		count_type),
	m_is_initialized(false)
{};

CContainerOfLogicalDisk::CContainerOfLogicalDisk(
	const CHardwareStatusSpecification& orig) :
	CHardwareStatusSpecification(orig), m_is_initialized(false)
{};

CContainerOfLogicalDisk::CContainerOfLogicalDisk(
	const CContainerOfLogicalDisk& orig) :
	CHardwareStatusSpecification(orig.m_pause_duration,
		orig.m_path_to_file, orig.m_count_type),
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
	DWORD buffer_size = c_size_of_buffer_for_api;
	char container_all_disks_names[c_size_of_buffer_for_api + 
								   c_size_of_buffer_for_api] = {};

	DWORD is_created_correct = GetLogicalDriveStrings(buffer_size,
		LPSTR(container_all_disks_names));

	if (is_created_correct > 0 &&
		is_created_correct <= c_size_of_buffer_for_api)
	{
		char* variable_for_checking_names = container_all_disks_names;

		while (*variable_for_checking_names)
		{

			std::string name_of_disk = variable_for_checking_names;

			if (!Utils::TryGetFormattedDiskName(name_of_disk))
			{
				return false;
			}
			CLogicalDiskStatus* created_disk = new CLogicalDiskStatus();

			if (!created_disk->InitializeLogicalDiskStatus(
				name_of_disk, m_count_type))
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

bool CContainerOfLogicalDisk::InitializeContainerOfLogicalDisk(
	CHardwareStatusSpecification& specification)
{
	m_pause_duration = specification.GetPauseDuration();
	m_path_to_file = *specification.GetPathToSaveFile();
	m_pause_duration = specification.GetPauseDuration();
	m_is_initialized = true;

	if (!TryGetAllExistedLogicalDisksAndInfo())
	{
		m_is_initialized = false;
		return false;
	}

	return true;
}

bool CContainerOfLogicalDisk::IsInitialized() const
{ return m_is_initialized; }

std::vector<CLogicalDiskStatus*>* CContainerOfLogicalDisk::GetAllLogicalDisk()
{
	if (!IsInitialized())
	{
		// will be changed after implementing an exception handler
		return nullptr;
	}
	return &m_p_container_all_logical_disks; 
}