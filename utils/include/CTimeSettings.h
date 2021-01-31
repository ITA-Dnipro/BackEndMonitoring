#pragma once
#include "CDataReader.h"

class CTimeSettings
{
public:
	CTimeSettings() = delete;
	CTimeSettings(CTimeSettings&) = delete;
	CTimeSettings(CTimeSettings&&) = delete;

	CTimeSettings(std::shared_ptr<CDataReader> p_data_reader);
	~CTimeSettings() = default;

	void ReadConfigurationFromFile();

	[[nodiscard]] int GetPeriodTime() const;

private:
	std::shared_ptr<CDataReader> p_data_reader_;
	int period_time_;
};
