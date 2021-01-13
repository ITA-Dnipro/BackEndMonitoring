#include "stdafx.h"
#include "ContainerOfLogicalDisk.h"

bool ContainerOfLogicalDisk::TryGetAllExistedLogicalDisksAndInfo()
{
	const unsigned short c_size_of_buffer_for_api = 1024;
	//We just skip 7 chars: ';', '/' and nul 
	const unsigned short number_of_chars_need_miss = 7;
	DWORD buffer_size = c_size_of_buffer_for_api;
	char container_all_disks_names[c_size_of_buffer_for_api * 2] = {};
	DWORD result_is_created_correct = GetLogicalDriveStrings(buffer_size,
		LPWSTR(container_all_disks_names));

	if (result_is_created_correct > 0 &&
		result_is_created_correct <= c_size_of_buffer_for_api)
	{
		char* variable_for_checking_names = container_all_disks_names;
		while (*variable_for_checking_names)
		{
			container_all_logical_disks_.push_back
				(LogicalDiskStatus::FactoryLogicalDiskStatus(
					(static_cast<std::string>
					(variable_for_checking_names)+":/"), count_type_));

			//go to the next driver
			variable_for_checking_names +=
				strlen(variable_for_checking_names)
				+ number_of_chars_need_miss;
		}
	}
	else
	{
		return false;
	}

	return true;

}

ContainerOfLogicalDisk* ContainerOfLogicalDisk::FactoryContainerOfLogicalDisk( 
	HardwareStatusSpecification* specification)
{
	ContainerOfLogicalDisk* container = new
		ContainerOfLogicalDisk(*specification);

	if (!container->TryGetAllExistedLogicalDisksAndInfo())
	{
		return nullptr;
	}

	return container;
}

std::vector<LogicalDiskStatus*>* ContainerOfLogicalDisk::GetAllLogicalDisk()
{
	return &container_all_logical_disks_;
}