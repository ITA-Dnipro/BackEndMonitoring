#pragma once

#include "CLogicalDiskStatus.h"
#include "ÑHardwareStatusSpecification.h"

class ÑContainerOfLogicalDisk : public ÑHardwareStatusSpecification
{
public:
	ÑContainerOfLogicalDisk() = delete;
	explicit ÑContainerOfLogicalDisk(
		std::chrono::duration<int> period_of_checking_status, 
		const std::string& path_to_file, EMemoryCountType count_type) :
		ÑHardwareStatusSpecification(period_of_checking_status, path_to_file,
			count_type)
	{ };
	explicit ÑContainerOfLogicalDisk(const ÑHardwareStatusSpecification& orig) 
		: ÑHardwareStatusSpecification(orig)
	{ };
	explicit ÑContainerOfLogicalDisk(const ÑContainerOfLogicalDisk& orig) :
		ÑHardwareStatusSpecification(orig.m_pause_duration, 
			orig.m_path_to_file, orig.m_count_type),
		m_p_container_all_logical_disks(orig.m_p_container_all_logical_disks)
	{ };
	ÑContainerOfLogicalDisk(const ÑContainerOfLogicalDisk&&) noexcept = delete;

	~ÑContainerOfLogicalDisk()
	{
		for (const auto& disk : m_p_container_all_logical_disks)
		{
			delete disk;
		}
	}

	[[nodiscard]] static ÑContainerOfLogicalDisk* 
		FactoryContainerOfLogicalDisk(
			const ÑHardwareStatusSpecification& specification);

	[[nodiscard]] std::vector<CLogicalDiskStatus*>* GetAllLogicalDisk();

private:
	[[nodiscard]] bool TryGetAllExistedLogicalDisksAndInfo();

	std::vector<CLogicalDiskStatus*> m_p_container_all_logical_disks;
};

