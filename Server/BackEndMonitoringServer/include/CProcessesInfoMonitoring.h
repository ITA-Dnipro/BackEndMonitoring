#pragma once

#include "IHardwareInfoMonitoring.h"
#include "CContainerOfProcesses.h"

class CJSONFormatterProcess;

class CProcessesInfoMonitoring : IHardwareInfoMonitoring
{
public:
	CProcessesInfoMonitoring() = delete;
	explicit CProcessesInfoMonitoring(
		std::chrono::duration<int> pause_duration,
		std::string path_to_file, EMemoryConvertType count_type, 
		CEvent& stop_event,
		CThreadSafeVariable<CJSONFormatterProcess>& json_formatter);

	CProcessesInfoMonitoring(const CProcessesInfoMonitoring&) 
		= delete;
	CProcessesInfoMonitoring(CProcessesInfoMonitoring&&) 
		noexcept = delete;
	~CProcessesInfoMonitoring() noexcept = default;

	bool Initialize();
	bool StartMonitoringInfo() override;

private:
	CContainerOfProcesses m_container;
	CThreadSafeVariable<CJSONFormatterProcess>& m_json_formatter;
	bool m_is_initialized;
};

