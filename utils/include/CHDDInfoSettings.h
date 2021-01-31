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
	std::shared_ptr<CDataReader> p_data_reader_;
	std::string file_name_;
	bool check_hdd_;
	int count_type_;
};
