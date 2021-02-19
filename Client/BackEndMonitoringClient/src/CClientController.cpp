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

bool CClientController::MakeRequest(ERequestType type, std::string& message)
{
	CLOG_DEBUG_START_FUNCTION();

	if (is_connected)
	{
		switch (type)
		{
		case (ERequestType::PROCESSES_DATA):
		{
			message = RequestProcessesData();
			break;
		}
		case (ERequestType::DISKS_DATA):
		{
			message = RequestDisksData();
			break;
		}
		case (ERequestType::ALL_DATA):
		{
			message = RequestAllData();
			break;
		}
		case (ERequestType::EXIT):
		{
			while (!m_connector->Exit())
				return false;
		}
		}
		if (message == "Error receiving data")
		{
			return false;
		}
		return true;
	}
	CLOG_DEBUG_END_FUNCTION();

	return false;
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

std::string CClientController::RequestProcessesData()
{
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_END_FUNCTION();
	return m_connector->MakeRequest(EClientRequestType::PROCESSES_DATA);
}

std::string CClientController::RequestDisksData()
{
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_END_FUNCTION();
	return m_connector->MakeRequest(EClientRequestType::DISKS_DATA);
}

std::string CClientController::RequestAllData()
{
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_END_FUNCTION();
	return m_connector->MakeRequest(EClientRequestType::ALL_DATA);
}
