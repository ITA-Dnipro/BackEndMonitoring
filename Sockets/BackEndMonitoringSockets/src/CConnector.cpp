#include "stdafx.h"

#include "CConnector.h"
#include "CSockAddress.h"
#include "Log.h"

CConnector::CConnector()
	: m_is_initialized(false)
{ }

CConnector::~CConnector() noexcept
{
	PlatformUtils::CloseSocket(m_socket_connector.GetSocketFD());
}

bool CConnector::Initialize(const int port, const std::string& address)
{
	CLOG_DEBUG_START_FUNCTION();
	if(m_is_initialized)
	{
		CLOG_DEBUG("CConnector has already been initialized");
		return true;
	}

	if(m_socket_connector.InitSocket())
	{
		m_socket_address = InitSocketAddress(address, port);
		m_is_initialized = true;
		CLOG_DEBUG("CConnector was successfully initialized");
	}
	CLOG_DEBUG_END_FUNCTION();
	return m_is_initialized;
}

bool CConnector::Connect() const
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();

	if(!m_is_initialized && !m_socket_connector.IsValidSocket())
	{
		CLOG_ERROR("CConnector is not initilized");
		return result;
	}
	
	if (PlatformUtils::Connect(m_socket_connector.GetSocketFD(), 
		m_socket_address->GetSocketAddress()))
    {
		CLOG_DEBUG_WITH_PARAMS("Client was successfully connected to the server", 
			m_socket_connector.GetSocketFD());
		result = true;
    }
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

CSocket& CConnector::GetSocket()
{
	CLOG_TRACE_START_FUNCTION();
	CLOG_TRACE_END_FUNCTION();
	return m_socket_connector;
}

std::unique_ptr<CSockAddress> CConnector::InitSocketAddress(const std::string& ip_address, const int port)
{
	CLOG_TRACE_START_FUNCTION();
	CLOG_TRACE_END_FUNCTION();
	return std::move(std::make_unique<CSockAddress>(port, ip_address));
}

