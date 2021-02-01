#pragma once
#include "ISettings.h"
#include "CDataReader.h"

class CSettings : public ISettings
{
public:
	CSettings() = delete;
	CSettings(const CSettings&) = delete;
	CSettings(CSettings&&) = delete;

	explicit CSettings(std::shared_ptr<CDataReader> p_data_reader);
	virtual ~CSettings() = default;

	void ReadConfigurationFromFile() override = 0;
protected:
	std::shared_ptr<CDataReader> m_p_data_reader_;

};
