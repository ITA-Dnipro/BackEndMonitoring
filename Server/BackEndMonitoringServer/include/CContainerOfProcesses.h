#pragma once

#include "CHardwareStatusSpecification.h"
#include "CProcess.h"

class CContainerOfProcesses : public ÑHardwareStatusSpecification
{
public:
	CContainerOfProcesses() = delete;
	explicit CContainerOfProcesses(unsigned, std::chrono::duration<int>,
						  std::string, EMemoryCountType);
	CContainerOfProcesses(const CContainerOfProcesses&) = delete;
	CContainerOfProcesses(CContainerOfProcesses&&) noexcept = delete;
	~CContainerOfProcesses() noexcept = default;

	bool TryToUpdateCurrentStatus();
	[[nodiscard]] std::vector<CProcess> GetAllProcesses();
private:
	bool GetListOfProcessIds(std::list<DWORD>& list_of_PIDs) const;

	std::vector<CProcess> m_container;
	const unsigned m_max_process_count;
	unsigned m_processors_count;
};

