#pragma once

#include "stdafx.h"
#include "EMemoryCountType.h"
#include "EConvertValueFromBytes.h"

class LogicalDiskStatus
{
public:
	LogicalDiskStatus() = delete;
	explicit LogicalDiskStatus(LogicalDiskStatus& orig) : 
		disk_name_(orig.disk_name_),
		disk_info_(orig.disk_info_)
	{ };
	LogicalDiskStatus(LogicalDiskStatus&&) noexcept = delete;

	[[nodiscard]] static LogicalDiskStatus* FactoryLogicalDiskStatus(
		std::string disk_name,
		EMemoryCountType count_type = EMemoryCountType::BYTES);

	[[nodiscard]] bool TryUpdateCurrentStatus();

	[[nodiscard]] std::string* GetDiskName();
	[[nodiscard]] long double GetCapacityOfDisk() const;
	[[nodiscard]] long double GetFreeSpaceOfDisk() const;

private:
	explicit LogicalDiskStatus( 
		std::string disk_name,
		EMemoryCountType count_type) :
		disk_name_(disk_name), count_type_(count_type)
	{ };
	
	[[nodiscard]] long double CalculateAsCountType(
		long double const value_to_calculate) const;

	std::string disk_name_;
	std::filesystem::space_info disk_info_{};
	EMemoryCountType count_type_ = EMemoryCountType::BYTES;
};


