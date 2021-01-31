#include "stdafx.h"
#include "CHDDInfoSettings.h"
#include "CLogger/include/Log.h"

CHDDInfoSettings::CHDDInfoSettings(std::shared_ptr<CDataReader> p_data_reader) :
	p_data_reader_(p_data_reader), file_name_("hddinfo.txt"), check_hdd_(true), count_type_(0)
{

}

void CHDDInfoSettings::ReadConfigurationFromFile()
{
	CLOG_DEBUG_START_FUNCTION();
	if (nullptr == p_data_reader_ || !p_data_reader_->IsFileInitialized())
	{
		p_data_reader_ ? CLOG_ERROR("Pointer to data reader is empty") :
			CLOG_ERROR("Data reader is not initialized");
		return;
	}

	std::string tmp_string;
	int tmp_int = 0;
	bool tmp_bool = false;

	if (p_data_reader_->TryToGetStringData("//root/Server/servername", tmp_string))
		file_name_ = tmp_string != "" ? tmp_string : file_name_;

	if (p_data_reader_->TryToGetStringData("//root/Server/serverdisplayname", tmp_string))
		check_hdd_ = CDataReader::TryToConvertToBool(tmp_string, tmp_bool) ? tmp_bool : check_hdd_;

	if (p_data_reader_->TryToGetStringData("//root/Server/listenerport", tmp_string))
		count_type_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int) ? tmp_int : count_type_;

	CLOG_DEBUG_END_FUNCTION();
}

std::string CHDDInfoSettings::GetFileName() const
{
	return file_name_;
}

bool CHDDInfoSettings::GetCheckHdd() const
{
	return check_hdd_;
}

int CHDDInfoSettings::GetCountType() const
{
	return count_type_;
}
