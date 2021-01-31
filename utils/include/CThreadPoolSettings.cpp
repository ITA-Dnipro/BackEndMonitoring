#include "stdafx.h"
#include "CThreadPoolSettings.h"
#include "CLogger/include/Log.h"

CThreadPoolSettings::CThreadPoolSettings(std::shared_ptr<CDataReader> p_data_reader) :
	p_data_reader_(p_data_reader), max_working_threads_(10)
{

}

void CThreadPoolSettings::ReadConfigurationFromFile()
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

	if (p_data_reader_->TryToGetStringData("//root/threadpool/maxworkingthreads", tmp_string))
		max_working_threads_ = CDataReader::TryToConvertToInteger(tmp_string, tmp_int) ? tmp_int : max_working_threads_;

	CLOG_DEBUG_END_FUNCTION();
}

int CThreadPoolSettings::GetMaxWorkingThreads() const
{
	return max_working_threads_;
}
