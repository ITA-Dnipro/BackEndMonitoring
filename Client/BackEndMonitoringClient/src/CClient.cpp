#include "stdafx.h"
#include "CClient.h"
#include "CLogger/include/Log.h"
#include "Sockets/BackEndMonitoringSockets/include/CConnectorWrapper.h"

CClient::CClient(int port, const std::string& ip_address)
	: m_port(port), m_ip_address(ip_address)
{
	InitLogger();
	m_connector = InitConnector();
}

CClient::~CClient()
{
	CLOG_DESTROY();
}

void CClient::MakeRequest()
{
	std::cout << "\t\tClient" << std::endl << std::endl;

	if (m_connector->ConnectToServer())
	{

		//while (GetRequestConfirmation())
		//{
		//	m_client_handler->HandleEvent(m_connector->GetSocket_fd(),
		//		EventType::REQUEST_DATA);
		//}
		int counter = 0;
		while (true)
		{
			//CLOG_DEBUG_WITH_PARAMS("Request to the server for the data ",
			//	counter);

			Sleep(500);
			std::cout << "-------- " << ++counter << " ---------" << std::endl;
			std::cout << m_connector->MakeRequest();
			if (counter == 20)
			{
				m_connector->Exit();
			}
		}
	}
	else
	{
		std::cout << "Cannot connect to the server!" << std::endl;
	}

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

std::unique_ptr<CConnectorWrapper> CClient::InitConnector()
{
	return std::move(std::make_unique<CConnectorWrapper>(m_port, m_ip_address));
}

bool CClient::GetRequestConfirmation()
{
	std::cout << "\t\tMenu" << std::endl
		<< "\t[1] - get current status from the server" << std::endl
		<< "\t[0] - exit" << std::endl;
	std::string choice;
	std::cin >> choice;

	if (choice == "1")
	{
		return true;
	}
	else if (choice == "0")
	{
		std::cout << "Goodbay!" << std::endl;
	}
	else
	{
		std::cout << "The wrong parameter has been passed, exit!" << std::endl;
	}

	return false;
}