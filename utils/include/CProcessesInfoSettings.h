#pragma once
#include "CDataReader.h"
#include "CSettings.h"

class CProcessesInfoSettings : public CSettings
{
public:
	CProcessesInfoSettings() = delete;
	CProcessesInfoSettings(const CProcessesInfoSettings&) = delete;
	CProcessesInfoSettings(CProcessesInfoSettings&&) = delete;

	explicit CProcessesInfoSettings(std::shared_ptr<CDataReader> p_data_reader);
	~CProcessesInfoSettings() override = default;

	void ReadConfigurationFromFile() override;

	[[nodiscard]] std::string GetFileName() const;
	[[nodiscard]] bool GetCheckProcesses() const;
	[[nodiscard]] int GetCountType() const;
	[[nodiscard]] int GetPeriodTime() const;

private:
	std::string m_file_name_;
	bool m_check_processes_;
	int m_count_type_;
	int m_period_time_;
};
