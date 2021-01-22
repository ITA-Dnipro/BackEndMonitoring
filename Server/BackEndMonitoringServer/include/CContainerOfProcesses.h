#pragma once

#include "CHardwareStatusSpecification.h"

class CProcess;

class CContainerOfProcesses : public CHardwareStatusSpecification
{
public:
	CContainerOfProcesses() = delete;
	explicit CContainerOfProcesses(unsigned, std::chrono::duration<int>,
		std::string, EMemoryCountType);
	CContainerOfProcesses(const CContainerOfProcesses&) = delete;
	CContainerOfProcesses(CContainerOfProcesses&&) noexcept = delete;
	~CContainerOfProcesses() noexcept = default;

	bool Initialize();
	bool TryToUpdateCurrentStatus();
	bool GetAllProcesses(std::vector<CProcess>& to_vector);
private:
	bool GetListOfProcessIds(std::list<DWORD>& list_of_PIDs) const;

private:
	bool m_is_initialized;
	std::vector<CProcess> m_container;
	const unsigned m_max_process_count;
	unsigned m_processors_count;
};

