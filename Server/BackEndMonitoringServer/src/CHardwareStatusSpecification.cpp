#include "stdafx.h"

#include "EMemoryCountType.h"
#include "CHardwareStatusSpecification.h"

std::chrono::duration<int> 
CHardwareStatusSpecification::GetPauseDuration() const
{ return m_pause_duration; }

EMemoryCountType CHardwareStatusSpecification::GetCountType() const
{ return m_count_type; }

std::string* CHardwareStatusSpecification::GetPathToSaveFile()
{ return &m_path_to_file; }
