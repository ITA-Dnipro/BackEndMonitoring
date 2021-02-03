#pragma once
#include "CDataReader.h"

class CHDDInfoSettings
{
public:
	CHDDInfoSettings() = delete;
	CHDDInfoSettings(CHDDInfoSettings&) = delete;
	CHDDInfoSettings(CHDDInfoSettings&&) = delete;
	
	explicit CHDDInfoSettings(std::shared_ptr<CDataReader> p_data_reader);
	
	~CHDDInfoSettings() = default;

	void ReadConfigurationFromFile();

	[[nodiscard]] std::string GetFileName() const;
	[[nodiscard]] bool GetCheckHdd() const;
	[[nodiscard]] int GetCountType () const;

private:
	std::shared_ptr<CDataReader> m_p_data_reader_;
	std::string m_file_name_;
	bool m_check_hdd_;
	int m_count_type_;
};
