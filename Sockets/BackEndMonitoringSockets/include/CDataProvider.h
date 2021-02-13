#pragma once

#include "IInfoDatabase.h"

class CDataProvider
{
public:
	CDataProvider() = delete;
	explicit CDataProvider(std::shared_ptr<IInfoDatabase> p_processes_data,
						   std::shared_ptr<IInfoDatabase> p_disks_data);
	~CDataProvider() noexcept = default;

	std::string GetProcessesInfo() const;
	std::string GetDisksInfo( ) const;
	std::string GetAllInfo( ) const;

private:
	std::shared_ptr<IInfoDatabase> m_p_processes_data;
	std::shared_ptr<IInfoDatabase> m_p_disks_data;
};

