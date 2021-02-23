#include "stdafx.h"

#include "ERequestType.h"
#include "CClient.h"
#include "Utils.h"
#include  "ClientUtils.h"
#include "Log.h"
#include "GlobalVariable.h"
#include "PlatformUtils.h"

CClient::CClient() :
	m_file_name("ServerResponses.txt"),
	m_controller(new CClientController), m_show_as_table(false),
	m_is_date_range_mode(false)
{
	Init();
}

void CClient::Init()
{
	CLOG_DEBUG_START_FUNCTION();

		std::filesystem::path path_to_file(m_file_name);
		std::filesystem::path extension = path_to_file.extension();
		std::filesystem::path name = path_to_file.stem();
		path_to_file.replace_filename(name.string() + extension.string());
		m_client_stream = std::fstream(path_to_file, std::ios_base::out);
		m_printer = std::make_unique<CClientView>(std::cout, m_client_stream, 
			std::cin);
		CLOG_DEBUG("CClientViews were initialized");
	CLOG_DEBUG_END_FUNCTION();
}

void CClient::Execute(const int arg_num, char** arguments)
{
	CLOG_DEBUG_START_FUNCTION();

	if(!EstablishConnectionWithServer(arg_num, arguments))
	{
		return;
	}
	
	bool result = true;
	EClientRequests client_request;
	ERequestType request_type;

	do
	{
		m_printer->PrintMenu(m_show_as_table, m_is_date_range_mode);
		client_request = m_printer->GetRequest();

		switch(client_request)
		{
		case EClientRequests::ERR:
			m_printer->PrintError();
			break;
		case EClientRequests::DISKS_DATA:
			result = MakeRequest(ERequestType::DISKS_DATA);
			break;
		case EClientRequests::PROCESSES_DATA:
			result = MakeRequest(ERequestType::PROCESSES_DATA);
			break;
		case EClientRequests::ALL_DATA:
			result = MakeRequest(ERequestType::ALL_DATA);
			break;
		case EClientRequests::ALL_DATA_CYCLE:
			result = MakeCycleOfRequests();
			break;
		case EClientRequests::ALL_DATA_NON_STOP:
			result = MakeNonStopRequests();
			break;
		case EClientRequests::DATE_MODE:
			m_is_date_range_mode = !m_is_date_range_mode;
			break;
		case EClientRequests::CHANGE_OUTPUT_TO_FILE:
			m_printer->SetIsWritingFile(!m_printer->GetIsWritingFile());
			break;
		case EClientRequests::CHANGE_VIEW_MODE:
			m_show_as_table = !m_show_as_table;
			break;
		case EClientRequests::CLS:
			PlatformUtils::CleanScreen();
			break;
		case EClientRequests::EXIT:
			MakeExitRequest();
			result = false;
			break;
		default:
			m_printer->PrintError();
			break;
		}

	} while (result && client_request != EClientRequests::EXIT);

	m_printer->PrintMessage("Goodbye\n");
	CLOG_DEBUG_END_FUNCTION();
}

bool CClient::MakeCycleOfRequests() const
{
	ERequestType request = ERequestType::ALL_DATA;
	bool result = false;
	std::string message;
	for (unsigned i = 1u; i <= 10u; ++i)
	{
		request = ERequestType::ALL_DATA;
		result = m_controller->MakeRequest(message, request,
			ERequestRangeSpecification::LAST_DATA);
		if (!message.empty())
		{
			m_printer->PrintMessage("\n" + std::to_string(i) + "\n\n" + message + "\n\n");
			message.clear();
		}
		if (!result)
		{
			break;
		}
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	return result;
}

bool CClient::MakeNonStopRequests() const
{
	int counter = 1;
	ERequestType request = ERequestType::ALL_DATA;
	bool result = false;
	std::string message;
	while (true)
	{
		result = m_controller->MakeRequest(message, request,
			ERequestRangeSpecification::LAST_DATA);
		if (!message.empty())
		{
			std::string message_new = resp_converter.ConvertResponse(message, ERequestType::ALL_DATA);
			m_printer->PrintMessage("\n" + std::to_string(counter++) + "\n\n" +
				message_new + "\n\n");
			message.clear();
		}
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	return result;
}

void CClient::MakeExitRequest() const
{
	m_controller->MakeExitRequest();
}

bool CClient::EstablishConnectionWithServer(const int arg_num, char** arguments)
{
	int port;
	std::string ip_address;
	
	if (arg_num == c_num_arguments)
	{
		port = ClientUtils::ConvertToInt(arguments[c_port_num]);
		ip_address = arguments[c_ip_address_num];

		if (ClientUtils::IsValidPort(port)
			&& ClientUtils::IsValidIpAddress(ip_address)
			&& m_controller->InitHost(port, ip_address)
			&& Connect(port, ip_address))
		{
			return true;
		}
	}
	m_printer->PrintErrorConnection();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	PlatformUtils::CleanScreen();

	std::string entered_port;
	std::string entered_address;
	do
	{
		entered_port = m_printer->EnterPort();
		if(entered_port.compare(g_c_client_requests[g_c_exit_request]) == 0)
		{
			return false;
		}
		entered_address = m_printer->EnterIpAddress();
		if (entered_address.compare(g_c_client_requests[g_c_exit_request]) == 0)
		{
			return false;
		}
		port = ClientUtils::ConvertToInt(entered_port);
		ip_address = entered_address;
		
		if(ClientUtils::IsValidPort(port)
			&& ClientUtils::IsValidIpAddress(ip_address)
			&& m_controller->InitHost(port, ip_address)
			&& Connect(port, ip_address))
		{
			return true;
		}

		m_printer->PrintErrorConnection();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		PlatformUtils::CleanScreen();

	} while (true);
}

bool CClient::Connect(const int port, const std::string& ip_address)
{
	bool result;

	if (m_controller->Connect())
	{
		m_printer->PrintSuccessConnection();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		PlatformUtils::CleanScreen();
		return true;
	}
	m_printer->PrintErrorConnection();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	PlatformUtils::CleanScreen();
	return false;
}

bool CClient::MakeRequest(ERequestType req_type) const
{
	std::string message;
	bool result = m_controller->MakeRequest(message,
		req_type, ERequestRangeSpecification::LAST_DATA);

	if (req_type != ERequestType::EXIT && !message.empty())
	{
		std::string message_new = resp_converter.ConvertResponse(message, req_type);
		m_printer->PrintMessage("\n" + message_new + "\n\n");
	}
	return result;
}
