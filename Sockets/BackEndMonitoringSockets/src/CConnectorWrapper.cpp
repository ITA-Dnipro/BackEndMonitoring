#include "stdafx.h"

#include "CClientConnectionHandler.h"
#include "CConnector.h"
#include "PlatformUtils.h"
#include "CLogger/include/Log.h"
#include "CConnectorWrapper.h"

CConnectorWrapper::CConnectorWrapper(int port, const std::string& ip_address)
	: m_port(port), m_address(ip_address)
{ 
	PlatformUtils::InitializeWinLibrary();
	m_p_client_handler = InitClientHandler();
	m_p_connector = InitConnector(m_port, m_address);
}

CConnectorWrapper::~CConnectorWrapper()
{
	PlatformUtils::CloseSocket(m_p_connector->GetSocketFD());
	PlatformUtils::FinalizeWinLibrary();
}

int CConnectorWrapper::GetClientSocket() const
{
	return m_p_connector->GetSocketFD();
}

std::string CConnectorWrapper::MakeRequest(EClientRequestType r_type) const
{
	std::string message;
	EEventType request_event = EEventType::REQUEST_ALL_DATA;
	if( r_type == EClientRequestType::ALL_DATA)
	{
		request_event = EEventType::REQUEST_ALL_DATA;
	}
	else if (r_type == EClientRequestType::DISKS_DATA)
	{
		request_event = EEventType::REQUEST_DISK_DATA;
	}
	else if (r_type == EClientRequestType::PROCESSES_DATA)
	{
		request_event = EEventType::REQUEST_PROCESS_DATA;
	}

	if (m_p_client_handler->HandleEvent(m_p_connector->GetSocketFD(),
		request_event, message))
	{
		return message;
	}
	return "Error receiving data";
}

bool CConnectorWrapper::ConnectToServer() const
{
	return m_p_connector->Connect();
}

bool CConnectorWrapper::Exit()
{
	std::string message;
	m_p_client_handler->HandleEvent(m_p_connector->GetSocketFD(),
		EEventType::CLOSE_EVENT, message);
	if (message == "Disconnect")
	{
		return true;
	}
	return false;
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
