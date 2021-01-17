#include "stdafx.h"

#include <iostream>
#include <fstream>
#include "Log.h"
#include "CConnectorWrapper.h"

int main()
{
	std::fstream stream("ClientLog.txt", std::ios_base::out);
	CLogBuilder builder("Logger", ELogLevel::DEBUG_LEVEL);
	builder.AddThreadUnsafeStream(stream).SetLogConfig(ELogConfig::CALL_TIME,
		ELogConfig::FILE_NAME, ELogConfig::FUNCTION_NAME,
		ELogConfig::LINE_NUMBER, ELogConfig::MESSAGE, ELogConfig::PARAMS);
	auto logger = builder.BuildSharedLog();
	int port = 1111;
	std::string ip_address = "127.0.0.1";

	CConnectorWrapper connector(port, ip_address, logger);

	connector.MakeRequest();

	system("pause");
}
