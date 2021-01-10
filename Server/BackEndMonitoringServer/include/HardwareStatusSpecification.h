#pragma once

#include "stdafx.h"
#include "EMemoryCountType.h"

class HardwareStatusSpecification
{
public:
	HardwareStatusSpecification() = delete;
	HardwareStatusSpecification(std::chrono::duration<int> pause_duration,
		std::string path_to_file, EMemoryCountType count_type) :
		pause_duration_(pause_duration), path_to_file_(path_to_file),
		count_type_(count_type)
	{ };
	HardwareStatusSpecification(HardwareStatusSpecification& orig) :
		pause_duration_(orig.pause_duration_), 
		path_to_file_(orig.path_to_file_),
		count_type_(orig.count_type_)
	{ };
	HardwareStatusSpecification(HardwareStatusSpecification&&) 
		noexcept = delete;

	[[nodiscard]] std::chrono::duration<int> GetPauseDuration() const;
	[[nodiscard]] EMemoryCountType GetCountType() const;
	[[nodiscard]] std::string* GetPathToSaveFile();

protected:
	// duration is used as seconds
	std::chrono::duration<int> pause_duration_{};
	// path to file where status of hardware will be storaged
	std::string path_to_file_;
	// Bytes - Megabytes - Gigabytes
	EMemoryCountType count_type_ = EMemoryCountType::BYTES;
};

