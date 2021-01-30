#include "stdafx.h"
#include "CConnectorWrapper.h"
#include "CClientConnectionHandler.h"
#include "CConnector.h"
#include "PlatformUtils.h"
#include "CLogger/include/Log.h"

#include <memory>
#include <string>
#include <future>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>

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

std::string CConnectorWrapper::MakeRequest() const
{
	while (true)	
	{
		if((m_client_handler->HandleEvent(m_connector->GetSocketFD(),
			EventType::REQUEST_DATA)))
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
