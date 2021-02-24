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

	if(!EstablishConnection(arg_num, arguments))
	{
		return;
	}
	PlatformUtils::CleanScreen();
	
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
		case EClientRequests::ALL_HISTORY:
			result = MakeAllHistoryRequest();
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

	m_printer->PrintMessage("Connection closed\n");
	CLOG_DEBUG_END_FUNCTION();
}

bool CClient::MakeCycleOfRequests()
{
	ERequestType request = ERequestType::ALL_DATA;
	bool result = true;
	std::string message;
	for (unsigned i = 1u; i <= 10u; ++i)
	{
		request = ERequestType::ALL_DATA;
		result = m_controller->MakeRequest(message, request,
			ERequestRangeSpecification::LAST_DATA);
		if (!message.empty())
		{
			m_printer->PrintMessage("\n\t\t\t" + std::to_string(i) + "\n");
			PrintMessage(message, request);
			message.clear();
		}
		if (!result || message.empty())
		{
			result = false;
			break;
		}
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	return result;
}

bool CClient::MakeNonStopRequests()
{
	int counter = 0;
	ERequestType request = ERequestType::ALL_DATA;
	bool result = true;
	std::string message;
	while (result)
	{
		result = m_controller->MakeRequest(message, request,
			ERequestRangeSpecification::LAST_DATA);
		if (result && !message.empty())
		{
			m_printer->PrintMessage("\n\t\t\t" + std::to_string(++counter) + "\n");
			PrintMessage(message, request);
			message.clear();
		}
		else
		{
			break;
		}
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	return result;
}

void CClient::MakeExitRequest() const
{
	m_controller->MakeExitRequest();
}

void CClient::PrintMessage(const std::string& message, ERequestType req_type)
{
	std::string converted_message = resp_converter.ConvertResponse(message,
		req_type, m_show_as_table);
	m_printer->PrintMessage("\n" + converted_message + "\n\n");
}

bool CClient::MakeAllHistoryRequest()
{
	std::string message;
	bool result = m_controller->MakeRequest(message,
		ERequestType::ALL_DATA, ERequestRangeSpecification::ALL_DATA);
	PrintMessage(message, ERequestType::ALL_DATA);
	return result;
}

bool CClient::EstablishConnection(const int arg_num, char** arguments)
{
	if (arg_num == static_cast<int>(Arguments::COUNT)
		&& ClientUtils::c_port_flag.compare(arguments[static_cast<int>(Arguments::PORT_FLAG)]) == 0
		&& ClientUtils::c_ip_address_flag.compare(arguments[static_cast<int>(Arguments::IP_FLAG)]) == 0)
	{
		int port = ClientUtils::ConvertToInt(arguments[static_cast<int>(Arguments::PORT)]);
		std::string ip_address = arguments[static_cast<int>(Arguments::IP)];

		if (ClientUtils::IsValidPort(port)
			&& ClientUtils::IsValidIpAddress(ip_address)
			&& m_controller->InitHost(port, ip_address)
			&& Connect(port, ip_address))
		{
			return true;
		}
	}
	m_printer->PrintMessage("Cannot connect to the server!\n");
	m_printer->PrintHelp();

	return false;
}

bool CClient::Connect(const int port, const std::string& ip_address)
{
	bool result;

	if (m_controller->Connect())
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		PlatformUtils::CleanScreen();
		return true;
	}
	std::this_thread::sleep_for(std::chrono::seconds(1));
	PlatformUtils::CleanScreen();
	return false;
}

bool CClient::MakeRequest(ERequestType req_type)
{
	std::string first_date;
	std::string second_date;

	if(m_is_date_range_mode)
	{
		m_printer->PrintMessage("Please, enter first date (format DD.MM.YY HH:MM:SS):\n");
		first_date = m_printer->EnterDate();
		m_printer->PrintMessage("Please, enter second date (format DD.MM.YY HH:MM:SS):\n");
		second_date = m_printer->EnterDate();
	}
	ERequestRangeSpecification req_specification = m_is_date_range_mode ? 
		ERequestRangeSpecification::RANGE_OF_DATA :
		ERequestRangeSpecification::LAST_DATA;
	
	std::string message;
	bool result = m_controller->MakeRequest(message,
		req_type, req_specification, first_date, second_date);

	if (req_type != ERequestType::EXIT && !message.empty())
	{
		PrintMessage(message, req_type);
	}
	return result;
}
