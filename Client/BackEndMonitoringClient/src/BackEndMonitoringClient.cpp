#include "stdafx.h"

#include <iostream>
#include <fstream>

#include "CLogger/include/Log.h"
#include "Sockets/BackEndMonitoringSockets/include/CConnectorWrapper.h"

int main()
{
	
	std::fstream fs("temp.log", std::ios_base::out);

	CLOG_START_CREATION();

	CLOG_SET_LOG_NAME("Logger");
	CLOG_SET_LOG_LEVEL(ELogLevel::DEBUG_LEVEL);
	CLOG_SET_LOG_CONFIG(ELogConfig::LOG_NAME, ELogConfig::LOG_LEVEL,
		ELogConfig::CALL_TIME, ELogConfig::THREAD_ID, ELogConfig::FILE_NAME,
		ELogConfig::FUNCTION_NAME, ELogConfig::LINE_NUMBER, ELogConfig::MESSAGE,
		ELogConfig::PARAMS);

	CLOG_ADD_SAFE_STREAM(fs);

	CLOG_BUILD();

	CLOG_END_CREATION();
	int port = 1111;
	std::string ip_address = "127.0.0.1";

	CConnectorWrapper connector(port, ip_address);

	connector.MakeRequest();
	CLOG_DESTROY();
	system("pause");
}
