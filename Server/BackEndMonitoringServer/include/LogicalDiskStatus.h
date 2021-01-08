#pragma once

#include "stdafx.h"
#include "HardwareStatus.h"
#include "EMemoryCountType.h"

class LogicalDiskStatus :
    public HardwareStatus
{
public:
	LogicalDiskStatus() = delete;
	explicit LogicalDiskStatus(LogicalDiskStatus& const orig) : 
		HardwareStatus(orig),
		all_drivers_info_(orig.all_drivers_info_) 
	{ };
	LogicalDiskStatus(LogicalDiskStatus&&) noexcept = delete;

	static LogicalDiskStatus* FactoryLogicalDiskStatus(
		std::chrono::duration<int> pause_duration,
		EMemoryCountType count_type = EMemoryCountType::BYTES);

	// todo: do we need methode: TryCheckIsAllDriversExist()
	bool TryUpdateCurrentStatus(std::string& disk_name);

	long long GetCapacityOfDisk(std::string& disk) const;
	long long GetFreeSpaceOnDisk(std::string& disk) const;

	virtual bool TryFormateDataToSaveFormat(std::string& data_storage) 
		override;
	virtual void ThreadWorkLogic() override;

private:
	explicit LogicalDiskStatus( 
		std::chrono::duration<int> pause_duration,
		EMemoryCountType count_type) :
		HardwareStatus(pause_duration), count_type_(count_type)
	{ };
	// todo: ask do I need this func
	bool TryChangeNameOfDiskAndUpdateInfo(std::string& old_disk_name, 
									   std::string& new_name);
	bool TryGetAllExistedLogicalDisksAndInfo(
		LogicalDiskStatus& created_object);
	bool TryUpdateCurrentStatus();
	long long CalculateAsCountType(long long const value_to_calculate) const;

	// todo: ask is it okey to declarate it here?
	enum class EConvertValueFromBytes
	{
		INTO_BYTES = 1,
		INTO_MEGABYTES = 1048576,
		INTO_GIGABYTES = 1073741824
	};

	std::map<std::string, std::filesystem::space_info> all_drivers_info_;
	EMemoryCountType count_type_ = EMemoryCountType::BYTES;
};


