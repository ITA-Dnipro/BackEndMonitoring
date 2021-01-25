#pragma once

#include "CHardwareStatusSpecification.h"

class CLogicalDiskInfo;

class CContainerOfLogicalDisk : public CHardwareStatusSpecification
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

	[[nodiscard]] bool InitializeContainerOfLogicalDisk(
			CHardwareStatusSpecification& specification);

	[[nodiscard]] bool IsInitialized() const;

	[[nodiscard]] std::vector<CLogicalDiskInfo*>* GetAllLogicalDisk();

private:
	[[nodiscard]] bool TryGetAllExistedLogicalDisksAndInfo();

	bool m_is_initialized;
	std::vector<CLogicalDiskInfo*> m_p_container_all_logical_disks;
};
