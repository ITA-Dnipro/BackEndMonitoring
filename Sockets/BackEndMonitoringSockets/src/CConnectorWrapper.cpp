#include "stdafx.h"
#include "CConnectorWrapper.h"
#include "CClientConnectionHandler.h"
#include "CConnector.h"
#include "PlatformUtils.h"
#include "CLogger/include/Log.h"

CConnectorWrapper::CConnectorWrapper(int port, const std::string& ip_address)
	: m_port(port), m_address(ip_address)
{ 
	PlatformUtils::InitializeWinLibrary();
	m_client_handler = InitClientHandler();
	m_connector = InitConnector(m_port, m_address);
}

CConnectorWrapper::~CConnectorWrapper()
{
	PlatformUtils::FinalizeWinLibrary();
}

void CConnectorWrapper::MakeRequest()
{
	std::cout << "\t\tClient" << std::endl << std::endl;

	if (ConnectToServer())
	{
		//while (GetRequestConfirmation())
		//{
		//	m_client_handler->HandleEvent(m_connector->GetSocket_fd(),
		//		EventType::REQUEST_DATA);
		//}
		int counter = 0;
		while (true)
		{
			m_client_handler->HandleEvent(m_connector->GetSocketFD(),
				EventType::REQUEST_DATA);
			CLOG_DEBUG_WITH_PARAMS("Requset to the server for the data ", counter);

			Sleep(1000);
			std::cout << "------------ " << ++counter << " ------------" << std::endl;
		}
	}

	std::cout << "Cannot connect to the server!" << std::endl;
}

bool CConnectorWrapper::GetRequestConfirmation()
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

bool CConnectorWrapper::ConnectToServer()
{
	return m_connector->Connect();
}

std::unique_ptr<CConnector> CConnectorWrapper::InitConnector(
	int port, const std::string& ip_address)
{
	return std::move(std::make_unique<CConnector>(port, ip_address));
}

std::unique_ptr<CClientConnectionHandler> CConnectorWrapper::InitClientHandler()
{
	return std::move(std::make_unique<CClientConnectionHandler>());
}
