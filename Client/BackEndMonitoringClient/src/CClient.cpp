#include "stdafx.h"

#include "CLogger/include/Log.h"
#include "Sockets/BackEndMonitoringSockets/include/CConnectorWrapper.h"
#include "ERequestType.h"

#include "CClient.h"

CClient::CClient(int port, const std::string& ip_address)
	: m_port(port), m_ip_address(ip_address), is_connected(false)
{
	InitLogger();
	m_connector = InitConnector();
}

bool CClient::Connect()
{
	is_connected = m_connector->ConnectToServer();
	return is_connected;
}

CClient::~CClient()
{
	CLOG_DESTROY();
}

bool CClient::MakeRequest(ERequestType type)
{
	bool result = true;
	if (is_connected)
	{
		switch (type)
		{
			case (ERequestType::PROCESSES_DATA):
			{
				result = RequestProcessesData();
				break;
			}
			case (ERequestType::DISKS_DATA):
			{
				result = RequestDisksData();
				break;
			}
			case (ERequestType::ALL_DATA):
			{
				result = RequestAllData();
				break;
			}
			case (ERequestType::EXIT):
			{
				m_connector->Exit();
				result = false;
				break;
			}

		}
	}
	return result;
}

void CClient::InitLogger()
{
	std::fstream fs("C:\\ClientLog.log", std::ios_base::out);

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

std::unique_ptr<CConnectorWrapper> CClient::InitConnector()
{
	return std::move(std::make_unique<CConnectorWrapper>(m_port, m_ip_address));
}

bool CClient::RequestProcessesData()
{
	return m_connector->MakeRequest(EClientRequestType::PROCESSES_DATA);
}

bool CClient::RequestDisksData()
{
	return m_connector->MakeRequest(EClientRequestType::DISKS_DATA);
}

bool CClient::RequestAllData()
{
	return m_connector->MakeRequest(EClientRequestType::ALL_DATA);
}