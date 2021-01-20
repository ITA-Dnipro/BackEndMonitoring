#include "stdafx.h"

#include <iostream>
#include <fstream>
#include "CAcceptorWrapper.h"
#include "CThreadPool.h"
#include "Log.h"
int main( )
{
	std::fstream stream("Log.txt", std::ios_base::out);
	CLogBuilder builder("Logger", ELogLevel::DEBUG_LEVEL);
	builder.AddThreadUnsafeStream(stream).SetLogConfig(ELogConfig::CALL_TIME, 
		ELogConfig::FILE_NAME, ELogConfig::FUNCTION_NAME, 
		ELogConfig::LINE_NUMBER, ELogConfig::MESSAGE, ELogConfig::PARAMS);
	auto logger = builder.BuildSharedLog();
	CEvent event;
	size_t num_threads = 20;
	int port = 1111;
	std::string ip_address = "127.0.0.1";
	WRITE_DEBUG(*logger, "Start server");
	CAcceptorWrapper acceptor(port, ip_address, num_threads, event, logger);

	acceptor.StartServer();
	system("pause");
	return 0;
}

