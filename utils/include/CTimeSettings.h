#pragma once
#include "CDataReader.h"

class CTimeSettings
{
public:
	CTimeSettings() = delete;
	CTimeSettings(const CTimeSettings&) = delete;
	CTimeSettings(CTimeSettings&&) = delete;

	explicit CTimeSettings(std::shared_ptr<CDataReader> p_data_reader);
	~CTimeSettings() = default;

	void ReadConfigurationFromFile();

	[[nodiscard]] int GetPeriodTime() const;

private:
	std::shared_ptr<CDataReader> m_p_data_reader_;
	int m_period_time_;
};
