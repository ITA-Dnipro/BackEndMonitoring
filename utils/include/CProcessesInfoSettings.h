#pragma once
#include "CDataReader.h"

class CProcessesInfoSettings
{
public:
	CProcessesInfoSettings() = delete;
	CProcessesInfoSettings(const CProcessesInfoSettings&) = delete;
	CProcessesInfoSettings(CProcessesInfoSettings&&) = delete;

	explicit CProcessesInfoSettings(std::shared_ptr<CDataReader> p_data_reader);
	~CProcessesInfoSettings() = default;

	void ReadConfigurationFromFile();

	[[nodiscard]] std::string GetFileName() const;
	[[nodiscard]] bool GetCheckHdd() const;
	[[nodiscard]] int GetCountType() const;

private:
	std::shared_ptr<CDataReader> p_data_reader_;
	std::string file_name_;
	bool check_processes_;
	int count_type_;
};
