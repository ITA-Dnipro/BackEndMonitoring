#include "stdafx.h"
#include "CHDDInfoSettings.h"
#include "CLogger/include/Log.h"

CHDDInfoSettings::CHDDInfoSettings(std::shared_ptr<CDataReader> p_data_reader) :
	m_p_data_reader_(p_data_reader), m_file_name_("hddinfo.txt"), m_check_hdd_(true), m_count_type_(0)
{

}

void CHDDInfoSettings::ReadConfigurationFromFile()
{
	CLOG_DEBUG_START_FUNCTION();
	if (nullptr == m_p_data_reader_ || !m_p_data_reader_->IsFileInitialized())
	{
		m_p_data_reader_ ? CLOG_ERROR("Pointer to data reader is empty") :
			CLOG_ERROR("Data reader is not initialized");
		return;
	}

	std::string tmp_string;
	int tmp_int = 0;
	bool tmp_bool = false;

	if (m_p_data_reader_->TryToGetStringData("//root/HDDinfo/filename", tmp_string))
		m_file_name_ = tmp_string != "" ? tmp_string : m_file_name_;

	if (m_p_data_reader_->TryToGetStringData("//root/HDDinfo/checkhdd", tmp_string))
		m_check_hdd_ = CDataReader::TryToConvertToBool(tmp_string, tmp_bool) ? tmp_bool : m_check_hdd_;

	if (m_p_data_reader_->TryToGetStringData("//root/HDDinfo/counttype", tmp_string))
		m_count_type_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int) ? tmp_int : m_count_type_;

	CLOG_DEBUG_END_FUNCTION();
}

std::string CHDDInfoSettings::GetFileName() const
{
	return m_file_name_;
}

bool CHDDInfoSettings::GetCheckHdd() const
{
	return m_check_hdd_;
}

int CHDDInfoSettings::GetCountType() const
{
	return m_count_type_;
}
