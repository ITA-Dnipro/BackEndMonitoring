#pragma once

#include "CHardwareInfoLifeCycle.h"
#include "CContainerOfProcesses.h"
#include "CJSONFormatterProcess.h"
#include "CThreadSafeVariable.h"

class CProcessesMonitoringLifeCycle : CHardwareInfoLifeCycle
{
public:
	CProcessesMonitoringLifeCycle() = delete;

	CProcessesMonitoringLifeCycle(unsigned max_size,
								  std::chrono::duration<int> pause_duration,
								  std::string path_to_file,
								  EMemoryCountType count_type,
								  CEvent& stop_event,
								  CThreadSafeVariable<CJSONFormatterProcess>& json_formatter);

	CProcessesMonitoringLifeCycle(const CProcessesMonitoringLifeCycle&) = delete;
	CProcessesMonitoringLifeCycle(CProcessesMonitoringLifeCycle&&) noexcept = delete;
	~CProcessesMonitoringLifeCycle() noexcept = default;

	void ThreadLifeCycle() override;

private:
	CContainerOfProcesses m_container;
	CThreadSafeVariable<CJSONFormatterProcess>& m_json_formatter;
};

