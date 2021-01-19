#include "stdafx.h"
#include "CConnectorWrapper.h"
CConnectorWrapper::CConnectorWrapper(int port, const std::string& ip_address, 
	std::shared_ptr<CLogger> logger)
	: m_port(port), m_address(ip_address), m_logger(logger)
{ }

void CConnectorWrapper::MakeRequest()
{
	std::cout << "\t\tClient" << std::endl << std::endl;

	std::unique_ptr<CConnector> connector;
	std::unique_ptr<CClientConnectionHandler> client_handler;

	while (GetRequestConfirmation())
	{
		connector = InitConnector(m_port, m_address);
		client_handler = InitClientHandler(connector->GetHandle());

		if (!ConnectToServer(std::move(connector), std::move(client_handler)))
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

bool CConnectorWrapper::ConnectToServer(std::unique_ptr<CConnector> connector, std::unique_ptr<CClientConnectionHandler> client_handler)
{
	if (connector->Connect())
	{
		client_handler->HandleEvent(connector->GetHandle(),
			EventType::REQUEST_DATA);
		return true;
	}

	return false;
}

std::unique_ptr<CConnector> CConnectorWrapper::InitConnector(
	int port, const std::string& ip_address)
{
	return std::move(std::make_unique<CConnector>(port, ip_address, m_logger));
}

std::unique_ptr<CClientConnectionHandler> CConnectorWrapper::InitClientHandler
	(int handle)
{
	return std::move(std::make_unique<CClientConnectionHandler>(handle, 
		m_logger));
}
