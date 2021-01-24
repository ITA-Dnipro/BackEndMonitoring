#pragma once

enum class EMemoryConvertType;

class CLogicalDiskInfo
{
public:
	CLogicalDiskInfo();
	explicit CLogicalDiskInfo(const CLogicalDiskInfo& orig);
	CLogicalDiskInfo(const CLogicalDiskInfo&&) noexcept = delete;

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
		EMemoryConvertType count_type) :
		m_disk_name(disk_name), m_count_type(count_type), 
		m_is_initialize(true)
	{ };
	
	[[nodiscard]] long double RoundToDecimal(long double const value_to_round) 
		const;

	bool m_is_initialize;
	std::string m_disk_name;
	std::filesystem::space_info m_disk_info{};
	EMemoryConvertType m_count_type;
};


