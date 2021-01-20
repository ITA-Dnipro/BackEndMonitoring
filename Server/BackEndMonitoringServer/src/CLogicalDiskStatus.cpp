#include "stdafx.h"

#include "EMemoryCountType.h"
#include "CLogicalDiskStatus.h"

CLogicalDiskStatus* CLogicalDiskStatus::FactoryLogicalDiskStatus(
	const std::string& disk_name,
	EMemoryCountType count_type)
{
	CLogicalDiskStatus* p_created_object = new CLogicalDiskStatus(
		disk_name, count_type);

	if (!p_created_object->TryUpdateCurrentStatus())
	{
		delete p_created_object;
		return nullptr;
	}

	return p_created_object;
}

bool CLogicalDiskStatus::TryUpdateCurrentStatus()
{
	//try-catch block for avoidind floppy disks
	try
	{
		m_disk_info = std::filesystem::space(m_disk_name);
	}
	catch (std::filesystem::filesystem_error&)
	{
		return false;
	}
	if (m_disk_info.capacity == 0 &&
		m_disk_info.available == 0 &&
		m_disk_info.free == 0)
	{
		return false;
	}

	return true;
}

std::string CLogicalDiskStatus::GetDiskName() const
{ return m_disk_name; }

long double CLogicalDiskStatus::GetCapacityOfDisk() const
{ return RoundToDecimal(CalculateAsCountType(m_disk_info.capacity)); }

long double CLogicalDiskStatus::GetAvailableOfDisk() const
{ return RoundToDecimal(CalculateAsCountType(m_disk_info.available)); }

long double CLogicalDiskStatus::GetFreeSpaceOfDisk() const
{ return RoundToDecimal(CalculateAsCountType(m_disk_info.free)); }

long double CLogicalDiskStatus::RoundToDecimal(
	long double const value_to_round) const
{ return round(value_to_round * 100.0) / 100.0; }

long double CLogicalDiskStatus::CalculateAsCountType(
	long double const value_to_calculate) const
{
	return static_cast<long double>(value_to_calculate)
		   /
		   static_cast<unsigned>(m_count_type);
}
