#pragma once
#include "CDataReader.h"
#include "CSettings.h"

class CTimeSettings : public CSettings
{
public:
	CTimeSettings() = delete;
	CTimeSettings(const CTimeSettings&) = delete;
	CTimeSettings(CTimeSettings&&) = delete;

	explicit CTimeSettings(std::shared_ptr<CDataReader> p_data_reader);
	~CTimeSettings() override = default;

	void ReadConfigurationFromFile() override;

	[[nodiscard]] int GetPeriodTime() const;

private:
	int m_period_time_;
};
