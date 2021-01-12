#pragma once

#include "EMemoryCountType.h"
#include "EConvertValueFromBytes.h"

class CLogicalDiskStatus
{
public:
	CLogicalDiskStatus() = delete;
	explicit CLogicalDiskStatus(const CLogicalDiskStatus& orig) : 
		m_disk_name(orig.m_disk_name),
		m_disk_info(orig.m_disk_info)
	{ };
	CLogicalDiskStatus(const CLogicalDiskStatus&&) noexcept = delete;

	[[nodiscard]] static CLogicalDiskStatus* FactoryLogicalDiskStatus(
		const std::string& disk_name,
		EMemoryCountType count_type = EMemoryCountType::BYTES);

	[[nodiscard]] bool TryUpdateCurrentStatus();

	[[nodiscard]] std::string* GetDiskName();
	[[nodiscard]] long double GetCapacityOfDisk() const;
	[[nodiscard]] long double GetFreeSpaceOfDisk() const;

private:
	explicit CLogicalDiskStatus( 
		const std::string& disk_name,
		EMemoryCountType count_type) :
		m_disk_name(disk_name), m_count_type(count_type)
	{ };
	
	[[nodiscard]] long double CalculateAsCountType(
		long double const value_to_calculate) const;

	std::string m_disk_name;
	std::filesystem::space_info m_disk_info{};
	EMemoryCountType m_count_type = EMemoryCountType::BYTES;
};


