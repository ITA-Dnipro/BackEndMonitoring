#pragma once

#include "CHardwareStatusSpecification.h"
#include "CProcessInfo.h"

class CContainerOfProcesses
{
public:
	CContainerOfProcesses() = delete;
	explicit CContainerOfProcesses(std::chrono::duration<int>,
		const std::string&, EMemoryConvertType);
	CContainerOfProcesses(const CContainerOfProcesses&) = delete;
	CContainerOfProcesses(CContainerOfProcesses&&) noexcept = delete;
	~CContainerOfProcesses() noexcept = default;

	[[nodiscard]]bool Initialize();

	[[nodiscard]]bool TryToUpdateCurrentStatus();

	[[nodiscard]]bool GetAllProcesses(std::list<CProcessInfo>& to_list);
	[[nodiscard]]const CHardwareStatusSpecification* GetSpecification() const;

private:
	void EraseDeadProcesses( );

	CHardwareStatusSpecification m_specification;
	std::list<CProcessInfo> m_container;
	bool m_is_initialized;
};

