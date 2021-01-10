#pragma once

#include "stdafx.h"
#include "LogicalDiskStatus.h"
#include "HardwareStatusSpecification.h"

class ContainerOfLogicalDisk : public HardwareStatusSpecification
{
public:
	ContainerOfLogicalDisk() = delete;
	ContainerOfLogicalDisk(
		std::chrono::duration<int> period_of_checking_status, 
		std::string path_to_file, EMemoryCountType count_type) :
		HardwareStatusSpecification(period_of_checking_status, path_to_file,
			count_type)
	{ };
	ContainerOfLogicalDisk(HardwareStatusSpecification& orig) :
		HardwareStatusSpecification(orig)
	{ };
	ContainerOfLogicalDisk(ContainerOfLogicalDisk& orig) : 
		HardwareStatusSpecification(orig.pause_duration_, orig.path_to_file_, 
			orig.count_type_),
		container_all_logical_disks_(orig.container_all_logical_disks_)
	{ };
	ContainerOfLogicalDisk(ContainerOfLogicalDisk&&) noexcept = delete;

	[[nodiscard]] static ContainerOfLogicalDisk* FactoryContainerOfLogicalDisk(
		HardwareStatusSpecification* specification);

	[[nodiscard]] std::vector<LogicalDiskStatus*>* GetAllLogicalDisk();

private:
	[[nodiscard]] bool TryGetAllExistedLogicalDisksAndInfo();

	std::vector<LogicalDiskStatus*> container_all_logical_disks_;
};

