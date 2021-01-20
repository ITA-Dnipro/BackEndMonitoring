#include "stdafx.h"
#include "CConnectorWrapper.h"
#include "CClientConnectionHandler.h"
#include "CConnector.h"

CConnectorWrapper::CConnectorWrapper(int port, const std::string& ip_address)
	: m_port(port), m_address(ip_address)
{ 
	m_client_handler = InitClientHandler();
}

void CConnectorWrapper::MakeRequest()
{
	std::cout << "\t\tClient" << std::endl << std::endl;

	std::unique_ptr<CConnector> connector;
	std::unique_ptr<CClientConnectionHandler> client_handler;

	while (GetRequestConfirmation())
	{
		connector = InitConnector(m_port, m_address);

		if (!ConnectToServer(std::move(connector)))
		{
			std::cout << "Cannot connect to the server!" << std::endl;
		}
	}
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

bool CConnectorWrapper::ConnectToServer(std::unique_ptr<CConnector> connector)
{
	if (connector->Connect())
	{
		m_client_handler->HandleEvent(connector->GetHandle(),
			EventType::REQUEST_DATA);
		return true;
	}

	return false;
}

std::unique_ptr<CConnector> CConnectorWrapper::InitConnector(
	int port, const std::string& ip_address)
{
	return std::move(std::make_unique<CConnector>(port, ip_address));
}

std::unique_ptr<CServiceHandler> CConnectorWrapper::InitClientHandler()
{
	return std::move(std::make_unique<CClientConnectionHandler>());
}
