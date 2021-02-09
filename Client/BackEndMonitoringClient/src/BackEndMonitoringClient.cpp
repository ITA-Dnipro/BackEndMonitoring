#include "stdafx.h"
#include "CLogger/include/Log.h"

#include "CClient.h"

int main(const int argc, char* argv[])
{
	std::string path_to_log_file("Log.txt");
	std::fstream log_stream = std::fstream(path_to_log_file, std::ios_base::app);

	CLOG_START_CREATION();

	CLOG_SET_LOG_NAME("Client Logger");
	CLOG_SET_LOG_LEVEL(ELogLevel::DEBUG_LEVEL);
	CLOG_SET_LOG_CONFIG(ELogConfig::LOG_NAME, ELogConfig::LOG_LEVEL,
		ELogConfig::CALL_TIME, ELogConfig::THREAD_ID, ELogConfig::FILE_NAME,
		ELogConfig::FUNCTION_NAME, ELogConfig::LINE_NUMBER, ELogConfig::MESSAGE,
		ELogConfig::PARAMS);

	CLOG_ADD_SAFE_STREAM(log_stream);

	CLOG_BUILD();

	CLOG_END_CREATION();

	CClient client;

	if (client.Init(argc, argv))
	{
		client.Execute();
	}
	else
	{
		std::cout << "Wrong parameters for the network!" << std::endl;
	}
	CLOG_DESTROY();
	return 0;
}