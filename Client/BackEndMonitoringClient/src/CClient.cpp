#include "stdafx.h"
#include "CClient.h"
#include "CLogger/include/Log.h"
#include "Sockets/BackEndMonitoringSockets/include/CConnectorWrapper.h"
CClient::CClient(int port, const std::string& ip_address)
	: m_port(port), m_ip_address(ip_address)
{
	InitLogger();
}

CClient::~CClient()
{
	CLOG_DESTROY();
}

void CClient::MakeRequest()
{
}

void CClient::InitLogger()
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
}
