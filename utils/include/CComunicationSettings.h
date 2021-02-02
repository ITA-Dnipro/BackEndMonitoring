#pragma once
#include "CDataReader.h"
#include "CSettings.h"

class CComunicationSettings : public CSettings
{
public:
	CComunicationSettings() = delete;
	CComunicationSettings(const CComunicationSettings&) = delete;
	CComunicationSettings(CComunicationSettings&&) = delete;
	
	explicit CComunicationSettings(std::shared_ptr<CDataReader> p_data_reader);
	
	~CComunicationSettings() override = default;

	void ReadConfigurationFromFile() override;

	[[nodiscard]] bool GetBlocking() const;
	[[nodiscard]] int GetSocketTimeout() const;
	
private:
	bool m_blocking_;
	int m_socket_timeout_;

};