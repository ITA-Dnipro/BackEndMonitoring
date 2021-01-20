#include "stdafx.h"

#include "EMemoryCountType.h"
#include "CLogicalDiskStatus.h"

bool CLogicalDiskStatus::InitializeLogicalDiskStatus(
	const std::string& disk_name,
	EMemoryCountType count_type)
{
	m_disk_name = disk_name; 
	m_count_type = count_type;
	m_is_initialize = true;

	if (!TryUpdateCurrentStatus())
	{
		m_is_initialize = false;
		return false;
	}

	return true;
}

bool CLogicalDiskStatus::IsInitialized() const
{ return m_is_initialize; }

bool CLogicalDiskStatus::TryUpdateCurrentStatus()
{
	if (!IsInitialized())
	{
		return false;
	}
	//try-catch block for avoidind floppy disks
	try
	{
		m_disk_info = std::filesystem::space(m_disk_name);
	}
	catch (std::filesystem::filesystem_error&)
	{
		return false;
	}
	if (m_disk_info.capacity == NULL &&
		m_disk_info.available == NULL &&
		m_disk_info.free == NULL)
	{
		return false;
	}

	return true;
}

std::string CLogicalDiskStatus::GetDiskName() const
{ 
	if (!IsInitialized())
	{
		// will be changed after implementing an exception handler
		return "";
	}
	return m_disk_name; 
}

long double CLogicalDiskStatus::GetCapacityOfDisk() const
{
	if (!IsInitialized())
	{
		// will be changed after implementing an exception handler
		return -1.0;
	}
	return RoundToDecimal(CalculateAsCountType(m_disk_info.capacity)); 
}

long double CLogicalDiskStatus::GetAvailableOfDisk() const
{
	if (!IsInitialized())
	{
		// will be changed after implementing an exception handler
		return -1.0;
	}
	return RoundToDecimal(CalculateAsCountType(m_disk_info.available)); 
}

long double CLogicalDiskStatus::GetFreeSpaceOfDisk() const
{
	if (!IsInitialized())
	{
		// will be changed after implementing an exception handler
		return -1.0;
	}
	return RoundToDecimal(CalculateAsCountType(m_disk_info.free)); }

long double CLogicalDiskStatus::RoundToDecimal(
	long double const value_to_round) const
{ 
	if (!IsInitialized())
	{
		// will be changed after implementing an exception handler
		return -1.0;
	}
	return round(value_to_round * 100.0) / 100.0; 
}

long double CLogicalDiskStatus::CalculateAsCountType(
	uintmax_t const value_to_calculate) const
{
	if (!IsInitialized())
	{
		// will be changed after implementing an exception handler
		return -1.0;
	}
	return static_cast<long double>(value_to_calculate)
		   /
		   static_cast<long double>(m_count_type);
}
