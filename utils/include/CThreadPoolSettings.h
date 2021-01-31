#pragma once
#include "CDataReader.h"

class CThreadPoolSettings
{
public:
	CThreadPoolSettings() = delete;
	CThreadPoolSettings(CThreadPoolSettings&) = delete;
	CThreadPoolSettings(CThreadPoolSettings&&) = delete;

	CThreadPoolSettings(std::shared_ptr<CDataReader> p_data_reader);
	~CThreadPoolSettings() = default;

	void ReadConfigurationFromFile();

	[[nodiscard]] int GetMaxWorkingThreads() const;

private:
	std::shared_ptr<CDataReader> p_data_reader_;
	int max_working_threads_;
};
