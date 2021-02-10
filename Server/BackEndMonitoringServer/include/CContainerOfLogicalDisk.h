#pragma once

#include "CHardwareStatusSpecification.h"

class CLogicalDiskInfo;
class CJSONFormatterLogicalDisk;

class CContainerOfLogicalDisk
{
public:
	CContainerOfLogicalDisk() = delete;
	explicit CContainerOfLogicalDisk(
		std::chrono::duration<int> period_of_checking_status,
		const std::string& path_to_file, EMemoryConvertType count_type);
	explicit CContainerOfLogicalDisk(const CHardwareStatusSpecification& orig);
	explicit CContainerOfLogicalDisk(const CContainerOfLogicalDisk& orig);

	CContainerOfLogicalDisk(const CContainerOfLogicalDisk&&) noexcept = delete;

	~CContainerOfLogicalDisk() noexcept;

	[[nodiscard]] bool InitializeContainerOfLogicalDisk();

	[[nodiscard]] bool IsInitialized() const;

	[[nodiscard]] bool TryUpdateInfoLogicalDiskToJSON(
		CJSONFormatterLogicalDisk& json_formatter);

	[[nodiscard]] const std::vector<CLogicalDiskInfo*>* GetAllLogicalDisk() 
		const;
	[[nodiscard]] CHardwareStatusSpecification* GetSpecification();

private:
	[[nodiscard]] bool TryGetAllExistedLogicalDisksAndInfo();

private:
	CHardwareStatusSpecification m_specification;
	std::vector<CLogicalDiskInfo*> m_p_container_all_logical_disks;
	bool m_is_initialized;
};

