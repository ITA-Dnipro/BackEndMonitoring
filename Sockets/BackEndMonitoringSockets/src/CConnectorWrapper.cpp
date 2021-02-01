#include "Sockets/BackEndMonitoringSockets/include/stdafx.h"

#include "CClientConnectionHandler.h"
#include "CConnector.h"
#include "PlatformUtils.h"
#include "Log.h"

#include "CConnectorWrapper.h"

CConnectorWrapper::CConnectorWrapper(int port, const std::string& ip_address)
	: m_port(port), m_address(ip_address)
{ 
	PlatformUtils::InitializeWinLibrary();
	m_client_handler = InitClientHandler();
	m_connector = InitConnector(m_port, m_address);
}

CConnectorWrapper::~CConnectorWrapper()
{
	PlatformUtils::CloseSocket(m_connector->GetSocketFD());
	PlatformUtils::FinalizeWinLibrary();
}

std::string CConnectorWrapper::MakeRequest(EClientRequestType r_type) const
{
	EventType request_event = EventType::REQUEST_ALL_DATA;
	if( r_type == EClientRequestType::ALL_DATA)
	{
		request_event = EventType::REQUEST_ALL_DATA;
	}
	else if (r_type == EClientRequestType::DISKS_DATA)
	{
		request_event = EventType::REQUEST_DISK_DATA;
	}
	else if (r_type == EClientRequestType::PROCESSES_DATA)
	{
		request_event = EventType::REQUEST_PROCESS_DATA;
	}
	else
	{
		return "";
	}
	while (true)	
	{
		if((m_client_handler->HandleEvent(m_connector->GetSocketFD(),
			request_event)))
		{
			break;
		}
	}

	return "";//m_response_holder.GetResponse();
}

bool CConnectorWrapper::ConnectToServer() const
{
	return m_connector->Connect();
}

void CConnectorWrapper::Exit()
{
	m_client_handler->HandleEvent(m_connector->GetSocketFD(),
		EventType::CLOSE_EVENT);
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
