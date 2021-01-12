#include "stdafx.h"
#include "CConnectorWrapper.h"

CConnectorWrapper::CConnectorWrapper()
{
	m_connector = InitConnector();
	m_stream = InitStream(m_connector->GetHandle());
	m_client_handler = std::make_unique<CClientConnectionHandler>
		(m_connector->GetHandle());
}

void CConnectorWrapper::MakeRequest(const std::string& message)
{
	Connect();

	m_client_handler->HandleEvent(m_connector->GetHandle(), 
		EventType::REQUEST_DATA);
}
//
//std::string CConnectorWrapper::GetResponse()
//{
//	return m_stream->Receive(m_handler->GetHandle());
//}
//
void CConnectorWrapper::Connect()
{
	m_connector->Connect();
}

std::unique_ptr<CConnector> CConnectorWrapper::InitConnector()
{
	return std::move(std::make_unique<CConnector>(1111, "127.0.0.1"));
}

std::unique_ptr<CSocketWrapper> CConnectorWrapper::InitStream(int handle)
{
	return std::move(std::make_unique<CSocketWrapper>(handle));
}
