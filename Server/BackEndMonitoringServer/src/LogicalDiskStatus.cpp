#include "stdafx.h"
#include "LogicalDiskStatus.h"

LogicalDiskStatus* LogicalDiskStatus::FactoryLogicalDiskStatus(
	std::string disk_name,
	EMemoryCountType count_type)
{
	LogicalDiskStatus* p_created_object = new LogicalDiskStatus(
		disk_name, count_type);
	if (!p_created_object->TryUpdateCurrentStatus())
	{
		return nullptr;
	}

	return p_created_object;
}

bool LogicalDiskStatus::TryUpdateCurrentStatus()
{
	disk_info_ = std::filesystem::space(disk_name_);
	if (disk_info_.capacity == NULL &&
		disk_info_.available == NULL &&
		disk_info_.free == NULL)
	{
		return false;
	}

	return true;
}

std::string* LogicalDiskStatus::GetDiskName()
{
	return &disk_name_;
}

long double LogicalDiskStatus::GetCapacityOfDisk() const
{ return CalculateAsCountType(disk_info_.capacity); }

long double LogicalDiskStatus::GetFreeSpaceOfDisk() const
{ return CalculateAsCountType(disk_info_.free); }

long double LogicalDiskStatus::CalculateAsCountType(
	long double const value_to_calculate) const
{
	switch (count_type_)
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
