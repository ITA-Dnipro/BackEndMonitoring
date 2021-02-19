#include "stdafx.h"
#include "CLogger/include/Log.h"

#include "CClient.h"

int main(const int argc, char* argv[])
{
	std::string path_to_log_file("Log.txt");
	std::fstream log_stream(path_to_log_file, std::ios_base::app);

	CLOG_CREATION_START();

	CLOG_CREATION_SET_LOG_NAME("Client Logger");
	CLOG_CREATION_SET_LOG_LEVEL(ELogLevel::DEBUG_LEVEL);
	CLOG_CREATION_SET_LOG_CONFIG(ELogConfig::LOG_NAME, ELogConfig::LOG_LEVEL,
		ELogConfig::CALL_TIME, ELogConfig::THREAD_ID, ELogConfig::FILE_NAME,
		ELogConfig::FUNCTION_NAME, ELogConfig::LINE_NUMBER, ELogConfig::MESSAGE,
		ELogConfig::PARAMS);

	CLOG_CREATION_ADD_SAFE_STREAM(log_stream);

	CLOG_BUILD();

	CLOG_CREATION_END();

	CClient client;

	if (client.Init(argc, argv))
	{
		client.Execute();
	}
	else
	{
		std::cout << "Wrong parameters for the network!" << std::endl;
	}
	return 0;
}