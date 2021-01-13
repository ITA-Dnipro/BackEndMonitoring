#pragma once

#include "EMemoryCountType.h"

class ÑHardwareStatusSpecification
{
public:
	ÑHardwareStatusSpecification() = delete;
	explicit ÑHardwareStatusSpecification(
		std::chrono::duration<int> 
		pause_duration, const std::string& path_to_file, 
		EMemoryCountType count_type) :
		m_pause_duration(pause_duration), m_path_to_file(path_to_file),
		m_count_type(count_type)
	{ };
	explicit ÑHardwareStatusSpecification(
		const ÑHardwareStatusSpecification& orig) :
		m_pause_duration(orig.m_pause_duration), 
		m_path_to_file(orig.m_path_to_file),
		m_count_type(orig.m_count_type)
	{ };
	ÑHardwareStatusSpecification(const ÑHardwareStatusSpecification&&) 
		noexcept = delete;

	[[nodiscard]] std::chrono::duration<int> GetPauseDuration() const;
	[[nodiscard]] EMemoryCountType GetCountType() const;
	[[nodiscard]] std::string* GetPathToSaveFile();

protected:
	// duration is used as seconds
	std::chrono::duration<int> m_pause_duration{};
	// path to file where status of hardware will be storaged
	std::string m_path_to_file;
	// Bytes - Megabytes - Gigabytes
	EMemoryCountType m_count_type = EMemoryCountType::BYTES;
};

