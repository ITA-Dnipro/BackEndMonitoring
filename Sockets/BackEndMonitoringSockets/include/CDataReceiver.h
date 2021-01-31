#pragma once
#include "CThreadSafeVariable.h"

class CJSONFormatterProcess;
class CJSONFormatterLogicalDisk;

class CDataReceiver
{
public:
	CDataReceiver(CThreadSafeVariable<CJSONFormatterProcess>& processes_json,
				  CThreadSafeVariable<CJSONFormatterLogicalDisk>& disks_json);

	std::string GetProcessesInfo();
	std::string GetDisksInfo( );
	std::string GetAllInfo( ) const;

private:
	CThreadSafeVariable<CJSONFormatterProcess>& m_processes_json;
	CThreadSafeVariable<CJSONFormatterLogicalDisk>& m_disks_json;
};

