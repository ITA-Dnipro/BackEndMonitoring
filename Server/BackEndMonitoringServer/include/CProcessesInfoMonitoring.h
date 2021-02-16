#pragma once

#include "IHardwareInfoMonitoring.h"
#include "CContainerOfProcesses.h"
#include "CProcessesInfoJSONDatabase.h"
#include "CResourcesInfoJSONDatabase.h"

class CProcessesInfoMonitoring : IHardwareInfoMonitoring
{
public:
	CProcessesInfoMonitoring( ) = delete;
	explicit CProcessesInfoMonitoring(
		std::chrono::duration<int> pause_duration,
		EMemoryConvertType count_type, CEvent& stop_event,
		std::shared_ptr<CProcessesInfoJSONDatabase> database,
		std::shared_ptr<CResourcesInfoJSONDatabase> resources_database);

	CProcessesInfoMonitoring(const CProcessesInfoMonitoring&) 
		= delete;
	CProcessesInfoMonitoring(CProcessesInfoMonitoring&&) 
		noexcept = delete;
	~CProcessesInfoMonitoring() noexcept = default;

	bool Initialize();
	bool StartMonitoringInfo() override;

private:
	CContainerOfProcesses m_container;
	std::shared_ptr<CProcessesInfoJSONDatabase> m_p_database;
	std::shared_ptr<CResourcesInfoJSONDatabase> m_p_resources_database;
	bool m_is_initialized;
};

