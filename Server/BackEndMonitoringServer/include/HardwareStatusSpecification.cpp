#include "stdafx.h"
#include "HardwareStatusSpecification.h"

std::chrono::duration<int> 
HardwareStatusSpecification::GetPauseDuration() const
{ return pause_duration_; }

EMemoryCountType HardwareStatusSpecification::GetCountType() const
{ return count_type_; }

std::string* HardwareStatusSpecification::GetPathToSaveFile()
{ return &path_to_file_; }
