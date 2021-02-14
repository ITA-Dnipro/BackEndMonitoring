#pragma once

#include "IInfoDatabase.h"
#include "CJSONFormatSaver.h"
#include "CMonitoringJSONDataContainer.h"

class IPathConstructor;

class CMonitoringInfoJSONDatabase : public IInfoDatabase
{
public:
	CMonitoringInfoJSONDatabase(std::filesystem::path path_to_file);
	CMonitoringInfoJSONDatabase(std::filesystem::path path_to_file, 
								const std::string& date_format);

	CMonitoringInfoJSONDatabase(const CMonitoringInfoJSONDatabase&) = delete;
	CMonitoringInfoJSONDatabase(CMonitoringInfoJSONDatabase&&) = delete;

	virtual ~CMonitoringInfoJSONDatabase( ) noexcept = default;

	bool GetAllInfo(std::string& data) override;
	bool GetLastInfo(std::string& data) override;
	bool GetSelectedInfo(time_t from, time_t to, std::string& data) override;

protected:
	std::filesystem::path m_path_to_file;
	std::mutex m_lock;
	const std::string m_date_format;
	CJSONFormatSaver m_saver;
	CMonitoringJSONDataContainer m_reader;
	std::shared_ptr<IPathConstructor> m_p_path_constructor;
};

