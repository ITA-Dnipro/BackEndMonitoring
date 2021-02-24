#include "stdafx.h"

#include "Utils.h"
#include "CLogger/include/Log.h"
#include "ERequestType.h"

#include "CClientController.h"

CClientController::CClientController()
	:m_port(0), is_connected(false)
{ }

bool CClientController::Connect()
{
	CLOG_DEBUG_START_FUNCTION();
	is_connected = m_connector->ConnectToServer();
	CLOG_DEBUG_WITH_PARAMS("We try connect to the server, result", is_connected);
	CLOG_DEBUG_END_FUNCTION();
	return is_connected;
}

bool CClientController::MakeRequest(std::string& message, ERequestType req_typ,
	ERequestRangeSpecification spec_typ,
	const std::string& date_of_start, const std::string& date_of_end)
{
	CLOG_DEBUG_START_FUNCTION();

	if (is_connected)
	{
		m_connector->MakeRequest(message, req_typ, EFrameError::NONE, spec_typ, date_of_start,
			date_of_end);
		if (message == "Error receiving data")
		{
			return false;
		}

		return true;
	}
	CLOG_DEBUG_END_FUNCTION();

	return false;
}

void CClientController::MakeExitRequest() const
{
	std::string message;
	m_connector->MakeRequest(message, ERequestType::EXIT, EFrameError::EXIT_MESSAGE);
}


bool CClientController::InitHost(const int port, const std::string& ip_address)
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	m_connector = std::make_unique<CClientConnectorHost>();
	result = m_connector->Initialize(port, ip_address);
	CLOG_DEBUG_WITH_PARAMS("Result of the InitHost function", result);
	if (result)
	{
		m_port = port;
		m_ip_address = ip_address;
	}
	CLOG_DEBUG_END_FUNCTION();
	return result;
}
