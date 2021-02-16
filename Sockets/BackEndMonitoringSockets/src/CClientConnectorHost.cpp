#include "stdafx.h"

#include "CLogger/include/Log.h"
#include "CClientConnectorHost.h"
#include "CConnector.h"

CClientConnectorHost::CClientConnectorHost(const int port, const std::string& ip_address)
{ 
	PlatformUtils::InitializeWinLibrary();
	m_p_client_handler = InitClientHandler();
	m_connector = InitConnector(port, ip_address);
	m_connector->Initialize();
}

CClientConnectorHost::~CClientConnectorHost()
{
	PlatformUtils::FinalizeWinLibrary();
}

std::string CClientConnectorHost::MakeRequest(EClientRequestType r_type) const
{
	std::string message;
	EEventType request_event = EEventType::LOST_REQUEST;
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

	if (m_p_client_handler->HandleEvent(m_connector->GetSocket(),
		request_event, message))
	{
		return message;
	}
	return "Error receiving data";
}

bool CClientConnectorHost::ConnectToServer() const
{
	return m_connector->Connect();
}

bool CClientConnectorHost::Exit() const
{
	std::string message;
	m_p_client_handler->HandleEvent(m_connector->GetSocket(),
		EEventType::CLOSE_EVENT, message);
	if (message.compare("Disconnect") == 0 || 
		message.compare("-1") == 0)
	{
		CLOG_DEBUG_WITH_PARAMS("Disconnect from the server, we receive response", 
			message);
		return true;
	}
	return false;
}

std::unique_ptr<CConnector> CClientConnectorHost::InitConnector(const int port,
	const std::string& ip_address)
{
	return std::move(std::make_unique<CConnector>(port, ip_address));
}

std::unique_ptr<CClientConnectionHandler> CClientConnectorHost::InitClientHandler()
{
	return std::move(std::make_unique<CClientConnectionHandler>());
}
