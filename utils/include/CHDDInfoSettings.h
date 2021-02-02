#pragma once
#include "CDataReader.h"
#include "CSettings.h"

class CHDDInfoSettings : public CSettings
{
public:
	CHDDInfoSettings() = delete;
	CHDDInfoSettings(CHDDInfoSettings&) = delete;
	CHDDInfoSettings(CHDDInfoSettings&&) = delete;
	
	explicit CHDDInfoSettings(std::shared_ptr<CDataReader> p_data_reader);
	
	~CHDDInfoSettings() override = default;

	void ReadConfigurationFromFile() override;

	[[nodiscard]] std::string GetFileName() const;
	[[nodiscard]] bool GetCheckHdd() const;
	[[nodiscard]] int GetCountType () const;
	[[nodiscard]] int GetPeriodTime() const;

private:
	std::string m_file_name_;
	bool m_check_hdd_;
	int m_count_type_;
	int m_period_time_;
};
