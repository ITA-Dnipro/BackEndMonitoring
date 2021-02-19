#include "stdafx.h"

#include "ERequestType.h"
#include "CClient.h"
#include "Utils.h"

#include "CLogger/include/Log.h"

CClient::CClient() : 
	m_file_name("ServerData_Client_.txt"),
	m_controller(new CClientController)
{ }

bool CClient::Init(const int arg_num, char** arguments)
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();

	if (arg_num != c_num_arguments)
	{
		return false;
	}

	int port = std::stol(arguments[c_port_num]);
	std::string ip_address = arguments[c_ip_address_num];

	result = m_controller->InitHost(port, ip_address);
	if (result)
	{
		std::filesystem::path path_to_file(m_file_name);
		std::filesystem::path extension = path_to_file.extension();
		std::filesystem::path name = path_to_file.stem();
		path_to_file.replace_filename(name.string() + extension.string());
		m_response_data = std::fstream(path_to_file, std::ios_base::out);
		m_consolePrinter = std::make_unique<CClientView>(std::cout, std::cin);
		m_filePrinter = std::make_unique<CClientView>(m_response_data, std::cin);
		CLOG_DEBUG("CClientViews were created");
	}
	CLOG_DEBUG_END_FUNCTION();

	return result;
}

void CClient::Execute()
{
	CLOG_DEBUG_START_FUNCTION();

	bool result = true;
	ERequestType request;
	std::string message;

	if (m_controller->Connect())
	{
		PrintMessage("Client connected to the server\n\n");
	}
	else
	{
		PrintMessage("Client cannot connect to the server, exit\n\n");
		return;
	}

	do
	{
		m_consolePrinter->PrintMenu();
		request = m_consolePrinter->GetRequest();

		switch (request)
		{
		case ERequestType::ERR:
			m_consolePrinter->PrintError();
			break;
		case ERequestType::ALL_DATA_CYCLE:
			for (unsigned i = 1u; i <= 10u; ++i)
			{
				result = m_controller->MakeRequest(ERequestType::ALL_DATA, message);
				if (!message.empty())
				{
					PrintMessage("\n" + std::to_string(i) + "\n\n" + message + "\n\n");
					message.clear();
				}
				if (!result)
				{
					break;
				}
				std::this_thread::sleep_for(std::chrono::seconds(5));
			}
			break;
		case ERequestType::ALL_DATA_NON_STOP:
		{
			int counter = 1;
			while (result)
			{
				result = m_controller->MakeRequest(ERequestType::ALL_DATA, message);
				if (!message.empty())
				{
					PrintMessage("\n" + std::to_string(counter++) + "\n\n" +
						message + "\n\n");
					message.clear();
				}
				std::this_thread::sleep_for(std::chrono::seconds(5));
			}
			break;
		}
		default:
			result = m_controller->MakeRequest(request, message);
			break;
		}
		if (!message.empty())
		{
			PrintMessage("\n" + message + "\n\n");
			message.clear();
		}

	} while (result && request != ERequestType::EXIT);

	PrintMessage("Goodbye\n");
	CLOG_DEBUG_END_FUNCTION();

}

void CClient::PrintMessage(const std::string& message) const
{
	CLOG_DEBUG_START_FUNCTION();
	m_consolePrinter->PrintMessage(message);
	m_filePrinter->PrintMessage(message);
	CLOG_DEBUG_END_FUNCTION();
}