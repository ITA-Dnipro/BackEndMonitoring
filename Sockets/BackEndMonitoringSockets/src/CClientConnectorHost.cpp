#include "stdafx.h"

#include "CLogger/include/Log.h"
#include "CClientConnectorHost.h"
#include "CConnector.h"
#include "GlobalVariable.h"

CClientConnectorHost::CClientConnectorHost() : m_is_initialized(false)
{ 
	PlatformUtils::InitializeWinLibrary();
}

CClientConnectorHost::~CClientConnectorHost()
{
	PlatformUtils::FinalizeWinLibrary();
}

bool CClientConnectorHost::Initialize(const int port, const std::string& ip_address)
{
	CLOG_DEBUG_START_FUNCTION();
	if(m_is_initialized)
	{
		CLOG_DEBUG("CClientConnectorHost has already been initialized");
		return true;
	}
	m_connector = InitConnector();
	if(m_connector->Initialize(port, ip_address))
	{
		m_p_client_handler = InitClientHandler();
		m_is_initialized = true;
		CLOG_DEBUG("CClientConnectorHost was successfuly initialized");
	}
	CLOG_DEBUG_END_FUNCTION();
	return m_is_initialized;
}

std::string CClientConnectorHost::MakeRequest(std::string& message, 
	ERequestType req_typ, ERequestRangeSpecification spec_typ,
	const std::string& date_of_start, const std::string& date_of_end) const
{
	CLOG_DEBUG_START_FUNCTION();
	if(!m_is_initialized)
	{
		CLOG_ERROR("Client host is not initialized");
		return "Client host is not initialized";
	}
	message.clear();

	if (m_p_client_handler->HandleEvent(m_connector->GetSocket(),
		message, req_typ, spec_typ, date_of_start, date_of_end))
	{
		CLOG_DEBUG_WITH_PARAMS("We receive message with length", message.size());
		return message;
	}
	CLOG_DEBUG_END_FUNCTION();
	return "Error receiving data";
}

bool CClientConnectorHost::ConnectToServer() const
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();

	if (!m_is_initialized)
	{
		CLOG_ERROR("CClientConnectorHost is not initialized");
		return false;
	}
	result = m_connector->Connect();
	CLOG_DEBUG_WITH_PARAMS("Result of connection to the server", result);
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

std::unique_ptr<CConnector> CClientConnectorHost::InitConnector()
{
	CLOG_TRACE_START_FUNCTION();
	CLOG_TRACE_END_FUNCTION();
	return std::move(std::make_unique<CConnector>());
}

std::unique_ptr<CClientConnectionHandler> CClientConnectorHost::InitClientHandler()
{
	CLOG_TRACE_START_FUNCTION();
	CLOG_TRACE_END_FUNCTION();
	return std::move(std::make_unique<CClientConnectionHandler>());
}
