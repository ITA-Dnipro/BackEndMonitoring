#pragma once

enum class EMemoryCountType;

class CLogicalDiskStatus
{
public:
	CLogicalDiskStatus() : m_is_initialize(false)
	{ };
	explicit CLogicalDiskStatus(const CLogicalDiskStatus& orig) : 
		m_disk_name(orig.m_disk_name),
		m_disk_info(orig.m_disk_info),
		m_count_type(orig.m_count_type),
		m_is_initialize(orig.m_is_initialize)
	{ };
	CLogicalDiskStatus(const CLogicalDiskStatus&&) noexcept = delete;

	[[nodiscard]] bool InitializeLogicalDiskStatus(
		const std::string& disk_name,
		EMemoryCountType count_type);

	[[nodiscard]] bool IsInitialized() const;

	[[nodiscard]] bool TryUpdateCurrentStatus();

	[[nodiscard]] std::string GetDiskName() const;
	[[nodiscard]] long double GetCapacityOfDisk() const;
	[[nodiscard]] long double GetAvailableOfDisk() const;
	[[nodiscard]] long double GetFreeSpaceOfDisk() const;

private:
	explicit CLogicalDiskStatus( 
		const std::string& disk_name,
		EMemoryCountType count_type) :
		m_disk_name(disk_name), m_count_type(count_type), 
		m_is_initialize(true)
	{ };
	
	[[nodiscard]] long double RoundToDecimal(long double const value_to_round) 
		const;

	[[nodiscard]] long double CalculateAsCountType(
		uintmax_t const value_to_calculate) const;

	bool m_is_initialize;
	std::string m_disk_name;
	std::filesystem::space_info m_disk_info{};
	EMemoryCountType m_count_type;
};


