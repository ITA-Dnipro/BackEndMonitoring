#pragma once

#include "CHardwareInfoLifeCycle.h"

class CJSONFormatterProcess;
class CContainerOfProcesses;

class CProcessesMonitoringLifeCycle : CHardwareInfoLifeCycle
{
public:
	CProcessesMonitoringLifeCycle() = delete;
	explicit CProcessesMonitoringLifeCycle(
		unsigned max_size, std::chrono::duration<int> pause_duration,
		std::string path_to_file, EMemoryCountType count_type, 
		CEvent& stop_event,
		CThreadSafeVariable<CJSONFormatterProcess>& json_formatter);

	CProcessesMonitoringLifeCycle(const CProcessesMonitoringLifeCycle&) 
		= delete;
	CProcessesMonitoringLifeCycle(CProcessesMonitoringLifeCycle&&) 
		noexcept = delete;
	~CProcessesMonitoringLifeCycle() noexcept = default;

	bool Initialize();
	bool ThreadLifeCycle() override;

private:
	bool m_is_initialized;
	CContainerOfProcesses m_container;
	CThreadSafeVariable<CJSONFormatterProcess>& m_json_formatter;
};

