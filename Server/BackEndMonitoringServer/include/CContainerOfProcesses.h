#pragma once

#include "CHardwareStatusSpecification.h"

class CProcessInfo;

class CContainerOfProcesses : public CHardwareStatusSpecification
{
public:
	CContainerOfProcesses() = delete;
	explicit CContainerOfProcesses(std::chrono::duration<int>,
		std::string, EMemoryConvertType);
	CContainerOfProcesses(const CContainerOfProcesses&) = delete;
	CContainerOfProcesses(CContainerOfProcesses&&) noexcept = delete;
	~CContainerOfProcesses() noexcept = default;

	bool Initialize();
	bool TryToUpdateCurrentStatus();
	bool GetAllProcesses(std::vector<CProcessInfo>& to_vector);

private:
	bool m_is_initialized;
	std::vector<CProcessInfo> m_container;
	unsigned m_processors_count;
};

