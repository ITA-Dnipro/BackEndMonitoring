#pragma once
#include "CDataReader.h"

class CThreadPoolSettings
{
public:
	CThreadPoolSettings() = delete;
	CThreadPoolSettings(const CThreadPoolSettings&) = delete;
	CThreadPoolSettings(CThreadPoolSettings&&) = delete;

	explicit CThreadPoolSettings(std::shared_ptr<CDataReader> p_data_reader);
	~CThreadPoolSettings() = default;

	void ReadConfigurationFromFile();

	[[nodiscard]] int GetMaxWorkingThreads() const;

private:
	std::shared_ptr<CDataReader> m_p_data_reader_;
	int m_max_working_threads_;
};
