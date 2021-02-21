#pragma once

#include "IInfoDatabase.h"

class CDataProvider
{
public:
	CDataProvider() = delete;
	explicit CDataProvider(std::shared_ptr<IInfoDatabase> p_processes_data,
						   std::shared_ptr<IInfoDatabase> p_disks_data,
						   std::shared_ptr<IInfoDatabase> p_resources_data);
	~CDataProvider() noexcept = default;

	std::string GetResourcesLoadLastInfo() const;
	std::string GetProcessesLastInfo() const;
	std::string GetDisksLastInfo( ) const;
	std::string GetAllLastInfo( ) const;

	std::string GetResourcesLoadFullInfo() const;
	std::string GetProcessesFullInfo() const;
	std::string GetDisksFullInfo() const;
	std::string GetAllFullInfo() const;

	std::string GetResourcesLoadSelectedInfo(time_t from, time_t to) const;
	std::string GetProcessesSelectedInfo(time_t from, time_t to) const;
	std::string GetDisksSelectedInfo(time_t from, time_t to) const;
	std::string GetAllSelectedInfo(time_t from, time_t to) const;
private:
	std::shared_ptr<IInfoDatabase> m_p_processes_data;
	std::shared_ptr<IInfoDatabase> m_p_disks_data;
	std::shared_ptr<IInfoDatabase> m_p_resources_data;
};

