#include "stdafx.h"

#include "CLogicalDiskStatus.h"

CLogicalDiskStatus* CLogicalDiskStatus::FactoryLogicalDiskStatus(
	const std::string& disk_name,
	EMemoryCountType count_type)
{
	CLogicalDiskStatus* p_created_object = new CLogicalDiskStatus(
		disk_name, count_type);
	if (!p_created_object->TryUpdateCurrentStatus())
	{
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
	if (m_disk_info.capacity == NULL &&
		m_disk_info.available == NULL &&
		m_disk_info.free == NULL)
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
	switch (m_count_type)

	{
	case EMemoryCountType::BYTES:
		return value_to_calculate / static_cast<long double>
			(EConvertValueFromBytes::INTO_BYTES);
		break;

	case EMemoryCountType::MEGABYTES:
		return value_to_calculate / static_cast<long double>
			(EConvertValueFromBytes::INTO_MEGABYTES);
		break;

	case EMemoryCountType::GIGABYTES:
		return value_to_calculate / static_cast<long double>
			(EConvertValueFromBytes::INTO_GIGABYTES);
		break;

	default:
		break;
	}

	return 0;
}