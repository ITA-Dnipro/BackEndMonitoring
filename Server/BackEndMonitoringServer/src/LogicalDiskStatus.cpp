#include "stdafx.h"
#include "LogicalDiskStatus.h"

bool LogicalDiskStatus::TryUpdateCurrentStatus()
{
	for (auto& pair_disk_info : all_drivers_info_)
	{
		pair_disk_info.second = std::filesystem::space(pair_disk_info.first);
		if (pair_disk_info.second.capacity == NULL &&
			pair_disk_info.second.available == NULL &&
			pair_disk_info.second.free == NULL)
		{
			return false;
		}
	}

	return true;
}

bool LogicalDiskStatus::TryUpdateCurrentStatus(std::string& disk_name)
{
	auto need_disk = all_drivers_info_.find(disk_name);
	if (need_disk == all_drivers_info_.end())
	{
		return false;
	}
	need_disk->second = std::filesystem::space(disk_name);
	// todo: ask isn't it unnecessary check?
	if (need_disk->second.capacity == NULL &&
		need_disk->second.available == NULL &&
		need_disk->second.free == NULL)
	{
		return false;
	}

	return true;
}

LogicalDiskStatus* LogicalDiskStatus::FactoryLogicalDiskStatus(
	std::chrono::duration<int> pause_duration,
	EMemoryCountType count_type)
{
	LogicalDiskStatus* p_created_object = new LogicalDiskStatus(
		pause_duration, count_type);
	if (!p_created_object->TryGetAllExistedLogicalDisksAndInfo(
		*p_created_object))
	{
		return nullptr;
	}

	return p_created_object;
}

bool LogicalDiskStatus::TryGetAllExistedLogicalDisksAndInfo(
	LogicalDiskStatus& created_object)
{
	const unsigned short c_size_of_buffer_for_api = 1024;
	//We just skip 7 chars: ';', '/' and nul 
	const unsigned short number_of_chars_need_miss = 7;
	DWORD buffer_size = c_size_of_buffer_for_api;
	char container_all_disks_names[c_size_of_buffer_for_api*2] = {};
	DWORD result_is_created_correct = GetLogicalDriveStrings(buffer_size, 
		LPWSTR(container_all_disks_names));

	if (result_is_created_correct > 0 && 
		result_is_created_correct <= c_size_of_buffer_for_api)
	{
		char* variable_for_checking_names = container_all_disks_names;
		while (*variable_for_checking_names)
		{
			created_object.all_drivers_info_.insert(
			std::map<std::string, std::filesystem::space_info>::value_type
				((static_cast<std::string>
					(variable_for_checking_names) + ":/"), 
				  std::filesystem::space((static_cast<std::string>
					(variable_for_checking_names)+":/"))));

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

long long LogicalDiskStatus::GetCapacityOfDisk(std::string& disk) const
{ 
	return CalculateAsCountType(all_drivers_info_.at(disk).capacity);
}

long long LogicalDiskStatus::GetFreeSpaceOnDisk(std::string& disk) const
{
	// todo: or better return available?
	return CalculateAsCountType(all_drivers_info_.at(disk).free);
}

bool LogicalDiskStatus::TryChangeNameOfDiskAndUpdateInfo(
	std::string& old_disk_name,
	std::string& new_name)
{
	auto pair_to_change = all_drivers_info_.extract(old_disk_name);
	
	if(pair_to_change.empty())
	{
		return false;
	}
	pair_to_change.key() = new_name;
	all_drivers_info_.insert(std::move(pair_to_change));
	//update changed disk
	return TryUpdateCurrentStatus(new_name);
}

long long LogicalDiskStatus::CalculateAsCountType(
	long long const value_to_calculate) const
{
	// todo: do I need static_cast?
	switch (count_type_)
	{
	case EMemoryCountType::BYTES:
		return value_to_calculate / static_cast<long long>
			(EConvertValueFromBytes::INTO_BYTES);
		break;
	case EMemoryCountType::MEGABYTES:
		return value_to_calculate / static_cast<long long>
			(EConvertValueFromBytes::INTO_MEGABYTES);
		break;
	case EMemoryCountType::GIGABYTES:
		return value_to_calculate / static_cast<long long>
			(EConvertValueFromBytes::INTO_GIGABYTES);
		break;
	default:
		break;
	}
	return 0;
}

bool LogicalDiskStatus::TryFormateDataToSaveFormat(std::string& data_storage)
{
	return false;
}

void LogicalDiskStatus::ThreadWorkLogic()
{
}
