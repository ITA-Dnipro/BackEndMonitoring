#pragma once
#include "CDataReader.h"
#include "CSettings.h"

class CThreadPoolSettings : public CSettings
{
public:
	CThreadPoolSettings() = delete;
	CThreadPoolSettings(const CThreadPoolSettings&) = delete;
	CThreadPoolSettings(CThreadPoolSettings&&) = delete;

	explicit CThreadPoolSettings(std::shared_ptr<CDataReader> p_data_reader);
	~CThreadPoolSettings() override = default;

	void ReadConfigurationFromFile() override;

	[[nodiscard]] int GetMaxWorkingThreads() const;

private:
	int m_max_working_threads_;
};
