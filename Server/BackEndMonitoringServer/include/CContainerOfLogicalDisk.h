#pragma once

#include "CHardwareStatusSpecification.h"

class CLogicalDiskStatus;

class CContainerOfLogicalDisk : public CHardwareStatusSpecification
{
public:
	CContainerOfLogicalDisk() = delete;
	explicit CContainerOfLogicalDisk(
		std::chrono::duration<int> period_of_checking_status,
		const std::string& path_to_file, EMemoryCountType count_type);
	explicit CContainerOfLogicalDisk(const CHardwareStatusSpecification& orig);
	explicit CContainerOfLogicalDisk(const CContainerOfLogicalDisk& orig);

	CContainerOfLogicalDisk(const CContainerOfLogicalDisk&&) noexcept = delete;

	~CContainerOfLogicalDisk() noexcept;

	[[nodiscard]] bool InitializeContainerOfLogicalDisk(
			CHardwareStatusSpecification& specification);

	[[nodiscard]] bool IsInitialized() const;

	[[nodiscard]] std::vector<CLogicalDiskStatus*>* GetAllLogicalDisk();

private:
	[[nodiscard]] bool TryGetAllExistedLogicalDisksAndInfo();

	bool m_is_initialized;
	std::vector<CLogicalDiskStatus*> m_p_container_all_logical_disks;
};

