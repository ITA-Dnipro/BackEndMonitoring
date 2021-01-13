#pragma once

#include "CHardwareInfoLifeCycle.h"
#include "CContainerOfProcesses.h"
#include "CJSONFormatterProcess.h"

class CProcessesMonitoringLifeCycle : CHardwareInfoLifeCycle
{
public:
	CProcessesMonitoringLifeCycle() = delete;
	CProcessesMonitoringLifeCycle(unsigned, std::chrono::duration<int>,
		std::string, EMemoryCountType, CEvent& stop_event);
	CProcessesMonitoringLifeCycle(const CProcessesMonitoringLifeCycle&) = delete;
	CProcessesMonitoringLifeCycle(CProcessesMonitoringLifeCycle&&) noexcept = delete;
	~CProcessesMonitoringLifeCycle() noexcept = default;

	void ThreadLifeCycle() override;

private:
	CContainerOfProcesses m_container;
};

