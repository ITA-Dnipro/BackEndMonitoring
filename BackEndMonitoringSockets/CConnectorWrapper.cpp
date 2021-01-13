#include "stdafx.h"
#include "CConnectorWrapper.h"

CConnectorWrapper::CConnectorWrapper(int port, const std::string& ip_address, 
	std::shared_ptr<CLogger> logger)
	: m_logger(logger)
{
	m_connector = InitConnector(port, ip_address);
	m_stream = InitStream(m_connector->GetHandle());
	m_client_handler = InitClientHandler(m_connector->GetHandle());
}

bool CConnectorWrapper::MakeRequest()
{
	if (Connect())
	{
		Sleep(5000);
		m_client_handler->HandleEvent(m_connector->GetHandle(),
			EventType::REQUEST_DATA);
		return true;
	}
	return false;
}

bool CConnectorWrapper::Connect()
{
	return m_connector->Connect();
}

std::unique_ptr<CConnector> CConnectorWrapper::InitConnector(
	int port, const std::string& ip_address)
{
	return std::move(std::make_unique<CConnector>(port, ip_address, m_logger));
}

std::unique_ptr<CSocketWrapper> CConnectorWrapper::InitStream(int handle)
{
	return std::move(std::make_unique<CSocketWrapper>(handle, m_logger));
}

std::unique_ptr<CClientConnectionHandler> CConnectorWrapper::InitClientHandler
	(int handle)
{
	return std::move(std::make_unique<CClientConnectionHandler>(handle, 
		m_logger));
}
