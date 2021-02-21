#include "stdafx.h"

#include "ERequestType.h"
#include "CClient.h"
#include "Utils.h"
#include "CLogger/include/Log.h"

CClient::CClient() : m_port(0),
	m_file_name("ServerData_Client_.txt"), is_connected(false)
{ }

bool CClient::Init(const int arg_num, char** arguments)
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();

	if (arg_num != c_num_arguments)
	{
		return false;
	}

	m_port = std::stol(arguments[c_port_num]);
	m_ip_address = arguments[c_ip_address_num];

	result = InitHost(m_port, m_ip_address);
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

	if (Connect())
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
				result = MakeRequest(ERequestType::ALL_DATA, message);
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
				result = MakeRequest(ERequestType::ALL_DATA, message);
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
		case ERequestType::ALL_DATA:
		{
			result = MakeRequest(request, message);
			nlohmann::json all_json = nlohmann::json::parse(message);

			nlohmann::json processes_json = nlohmann::json::parse(all_json["processes info"].get<std::string>());
			nlohmann::json disks_json = nlohmann::json::parse(all_json["disks info"].get<std::string>());

			all_json["processes info"] = processes_json.dump();
			all_json["disks info"] = disks_json.dump();

			message = all_json.dump();
			break;
		}
		default:
			result = MakeRequest(request, message);
			nlohmann::json parsed_json = nlohmann::json::parse(message);
			message = parsed_json.dump();
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

bool CClient::Connect()
{
	CLOG_DEBUG_START_FUNCTION();
	is_connected = m_connector->ConnectToServer();
	CLOG_DEBUG_WITH_PARAMS("We try connect to the server, result", is_connected);
	CLOG_DEBUG_END_FUNCTION();
	return is_connected;
}

bool CClient::MakeRequest(ERequestType type, std::string& message)
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

bool CClient::InitHost(const int port, const std::string& ip_address)
{
	bool result = false;
	CLOG_DEBUG_START_FUNCTION();
	m_connector = std::make_unique<CClientConnectorHost>();
	result = m_connector->Initialize(port, ip_address);
	CLOG_DEBUG_WITH_PARAMS("Result of the InitHost function", result);
	CLOG_DEBUG_END_FUNCTION();
	return result;
}

std::string CClient::RequestProcessesData()
{
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_END_FUNCTION();
	return m_connector->MakeRequest(EClientRequestType::PROCESSES_DATA);
}

std::string CClient::RequestDisksData()
{
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_END_FUNCTION();
	return m_connector->MakeRequest(EClientRequestType::DISKS_DATA);
}

std::string CClient::RequestAllData()
{
	CLOG_DEBUG_START_FUNCTION();
	CLOG_DEBUG_END_FUNCTION();
	return m_connector->MakeRequest(EClientRequestType::ALL_DATA);
}

void CClient::PrintMessage(const std::string& message) const
{
	CLOG_DEBUG_START_FUNCTION();
	m_consolePrinter->PrintMessage(message);
	m_filePrinter->PrintMessage(message);
	CLOG_DEBUG_END_FUNCTION();
}