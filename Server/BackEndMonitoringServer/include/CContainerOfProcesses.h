#pragma once

#include "CHardwareStatusSpecification.h"

class CProcess;

class CContainerOfProcesses : public CHardwareStatusSpecification
{
public:
	CContainerOfProcesses() = delete;
	explicit CContainerOfProcesses(std::chrono::duration<int>,
		std::string, EMemoryCountType);
	CContainerOfProcesses(const CContainerOfProcesses&) = delete;
	CContainerOfProcesses(CContainerOfProcesses&&) noexcept = delete;
	~CContainerOfProcesses() noexcept = default;

	bool Initialize();
	bool TryToUpdateCurrentStatus();
	bool GetAllProcesses(std::vector<CProcess>& to_vector);

private:
	bool m_is_initialized;
	std::vector<CProcess> m_container;
	unsigned m_processors_count;
};

