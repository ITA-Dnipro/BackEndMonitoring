#pragma once

#include "CLogicalDiskStatus.h"
#include "�HardwareStatusSpecification.h"

class �ContainerOfLogicalDisk : public �HardwareStatusSpecification
{
public:
	�ContainerOfLogicalDisk() = delete;
	explicit �ContainerOfLogicalDisk(
		std::chrono::duration<int> period_of_checking_status, 
		const std::string& path_to_file, EMemoryCountType count_type) :
		�HardwareStatusSpecification(period_of_checking_status, path_to_file,
			count_type)
	{ };
	explicit �ContainerOfLogicalDisk(const �HardwareStatusSpecification& orig) 
		: �HardwareStatusSpecification(orig)
	{ };
	explicit �ContainerOfLogicalDisk(const �ContainerOfLogicalDisk& orig) :
		�HardwareStatusSpecification(orig.m_pause_duration, 
			orig.m_path_to_file, orig.m_count_type),
		m_p_container_all_logical_disks(orig.m_p_container_all_logical_disks)
	{ };
	�ContainerOfLogicalDisk(const �ContainerOfLogicalDisk&&) noexcept = delete;

	~�ContainerOfLogicalDisk()
	{
		for (const auto& disk : m_p_container_all_logical_disks)
		{
			delete disk;
		}
	}

	[[nodiscard]] static �ContainerOfLogicalDisk* 
		FactoryContainerOfLogicalDisk(
			const �HardwareStatusSpecification& specification);

	[[nodiscard]] std::vector<CLogicalDiskStatus*>* GetAllLogicalDisk();

private:
	[[nodiscard]] bool TryGetAllExistedLogicalDisksAndInfo();

	std::vector<CLogicalDiskStatus*> m_p_container_all_logical_disks;
};

