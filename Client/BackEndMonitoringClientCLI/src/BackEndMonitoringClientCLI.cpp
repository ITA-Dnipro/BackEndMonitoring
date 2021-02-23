#include "stdafx.h"
#include "CLogger/include/Log.h"

#include "CClient.h"

int main(const int argc, char* argv[])
{
	std::string path_to_log_file("Log.txt");
	std::fstream log_stream(path_to_log_file, std::ios_base::app);

	CLOG_CREATION_START();

	CLOG_CREATION_SET_LOG_NAME("Client Logger");
	CLOG_CREATION_SET_DEBUG();
	CLOG_CREATION_SET_LOG_FLUSH(ELogFlush::FLUSH);
	CLOG_CREATION_SET_LOG_CONFIG(
		ELogConfig::THREAD_ID, ELogConfig::CALL_TIME,
		ELogConfig::LOG_LEVEL, ELogConfig::MESSAGE,
		ELogConfig::FUNCTION_NAME, ELogConfig::PARAMS);

	CLOG_CREATION_ADD_SAFE_STREAM(log_stream);

	CLOG_BUILD();

	CLOG_CREATION_END();

	CClient client;

	client.Execute(argc, argv);

	return 0;
}