#pragma once

#include "CHardwareStatusSpecification.h"

class CProcessInfo;

class CContainerOfProcesses
{
public:
	CContainerOfProcesses() = delete;
	explicit CContainerOfProcesses(std::chrono::duration<int>,
		std::string, EMemoryConvertType);
	CContainerOfProcesses(const CContainerOfProcesses&) = delete;
	CContainerOfProcesses(CContainerOfProcesses&&) noexcept = delete;
	~CContainerOfProcesses() noexcept = default;

	[[nodiscard]]bool Initialize();

	[[nodiscard]]bool TryToUpdateCurrentStatus();

	[[nodiscard]]bool GetAllProcesses(std::list<CProcessInfo>& to_list);
	[[nodiscard]]const CHardwareStatusSpecification* GetSpecification() const;

private:
	CHardwareStatusSpecification m_specification;
	std::list<CProcessInfo> m_container;
	unsigned m_processors_count;
	bool m_is_initialized;
};

