#pragma once
#include "CDataReader.h"

class CComunicationSettings
{
public:
	CComunicationSettings() = delete;
	CComunicationSettings(const CComunicationSettings&) = delete;
	CComunicationSettings(CComunicationSettings&&) = delete;
	
	explicit CComunicationSettings(std::shared_ptr<CDataReader> p_data_reader);
	
	~CComunicationSettings() = default;

	void ReadConfigurationFromFile();

	[[nodiscard]] bool GetBlocking() const;
	[[nodiscard]] int GetSocketTimeout() const;
	
private:
	std::shared_ptr<CDataReader> p_data_reader_ = nullptr;

	bool blocking_ = false;
	int socket_timeout_ = 5;

};