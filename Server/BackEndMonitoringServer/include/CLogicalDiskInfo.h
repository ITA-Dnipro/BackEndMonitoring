#pragma once

enum class EMemoryConvertType;

class CLogicalDiskInfo
{
public:
	CLogicalDiskInfo();
	explicit CLogicalDiskInfo(const CLogicalDiskInfo& orig);
	CLogicalDiskInfo(CLogicalDiskInfo&& orig) noexcept;

	[[nodiscard]] bool InitializeLogicalDiskStatus(
		const std::string& disk_name,
		EMemoryConvertType count_type);

	[[nodiscard]] bool IsInitialized() const;

	[[nodiscard]] bool TryUpdateCurrentStatus();

	[[nodiscard]] std::string GetDiskName() const;
	[[nodiscard]] long double GetCapacityOfDisk() const;
	[[nodiscard]] long double GetAvailableOfDisk() const;
	[[nodiscard]] long double GetFreeSpaceOfDisk() const;

private:
	explicit CLogicalDiskInfo(
		const std::string& disk_name,
		EMemoryConvertType count_type);
	
private:
	std::filesystem::space_info m_disk_info{};
	std::string m_disk_name;
	EMemoryConvertType m_count_type;
	bool m_is_initialize;
};


