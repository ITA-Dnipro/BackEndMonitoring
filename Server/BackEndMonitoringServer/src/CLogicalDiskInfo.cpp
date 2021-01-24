#include "stdafx.h"

#include "EMemoryConvertType.h"
#include "CLogicalDiskInfo.h"
#include "Utils.h"

CLogicalDiskInfo::CLogicalDiskInfo() : m_is_initialize(false)
{ };

CLogicalDiskInfo::CLogicalDiskInfo(const CLogicalDiskInfo& orig) :
	m_disk_name(orig.m_disk_name),
	m_disk_info(orig.m_disk_info),
	m_count_type(orig.m_count_type),
	m_is_initialize(orig.m_is_initialize)
{ };

bool CLogicalDiskInfo::InitializeLogicalDiskStatus(
	const std::string& disk_name,
	EMemoryConvertType count_type)
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

bool CLogicalDiskInfo::IsInitialized() const
{ return m_is_initialize; }

bool CLogicalDiskInfo::TryUpdateCurrentStatus()
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

std::string CLogicalDiskInfo::GetDiskName() const
{ 
	if (!IsInitialized())
	{
		// will be changed after implementing an exception handler
		return "";
	}
	return m_disk_name; 
}

long double CLogicalDiskInfo::GetCapacityOfDisk() const
{
	if (!IsInitialized())
	{
		// will be changed after implementing an exception handler
		return -1.0;
	}
	return RoundToDecimal(Utils::ConvertToCountType(m_disk_info.capacity,
													m_count_type));
}

long double CLogicalDiskInfo::GetAvailableOfDisk() const
{
	if (!IsInitialized())
	{
		// will be changed after implementing an exception handler
		return -1.0;
	}
	return RoundToDecimal(Utils::ConvertToCountType(m_disk_info.available, 
													m_count_type));
}

long double CLogicalDiskInfo::GetFreeSpaceOfDisk() const
{
	if (!IsInitialized())
	{
		// will be changed after implementing an exception handler
		return -1.0;
	}
	return RoundToDecimal(Utils::ConvertToCountType(m_disk_info.free, 
													m_count_type)); }

long double CLogicalDiskInfo::RoundToDecimal(
	long double const value_to_round) const
{ 
	if (!IsInitialized())
	{
		// will be changed after implementing an exception handler
		return -1.0;
	}
	return round(value_to_round * 100.0) / 100.0; 
}
