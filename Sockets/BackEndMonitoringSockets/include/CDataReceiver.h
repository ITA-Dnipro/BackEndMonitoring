#pragma once
#include "utils/include/CThreadSafeVariable.h"

class CJSONFormatterProcess;
class CJSONFormatterLogicalDisk;

class CDataReceiver
{
public:
	CDataReceiver() = delete;
	explicit CDataReceiver(CThreadSafeVariable<CJSONFormatterProcess>& processes_json,
				  CThreadSafeVariable<CJSONFormatterLogicalDisk>& disks_json);
	~CDataReceiver() noexcept = default;

	std::string GetProcessesInfo() const;
	std::string GetDisksInfo( ) const;
	std::string GetAllInfo( ) const;

private:
	CThreadSafeVariable<CJSONFormatterProcess>& m_p_processes_json;
	CThreadSafeVariable<CJSONFormatterLogicalDisk>& m_p_disks_json;
};

