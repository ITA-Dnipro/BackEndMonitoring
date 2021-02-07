#include "stdafx.h"

#include "ERequestType.h"
#include "ERequestType.h"
#include "CClient.h"
#include "Utils.h"

CClient::CClient() : m_port(0), is_connected(false)
{
	m_file_name = "ServerData_Client_.txt";
}

bool CClient::Init(const int arg_num, char** arguments)
{
	if (arg_num != c_num_arguments)
	{
		return false;
	}

	m_port = std::stol(arguments[c_port_num]);
	m_ip_address = arguments[c_ip_address_num];

	m_connector = InitConnector();
	std::filesystem::path path_to_file(m_file_name);
	std::filesystem::path extension = path_to_file.extension();
	std::filesystem::path name = path_to_file.stem();
	path_to_file.replace_filename(name.string() +
		std::to_string(m_connector->GetClientSocket()) + extension.string());
	m_response_data = std::fstream(path_to_file, std::ios_base::out);
	m_consolePrinter = std::make_unique<CClientView>(std::cout, std::cin);
	m_filePrinter = std::make_unique<CClientView>(m_response_data, std::cin);

	return true;
}

void CClient::Execute()
{
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
			for (unsigned i = 1u; i <= 10; ++i)
			{
				result = MakeRequest(ERequestType::ALL_DATA, message);
				if (message.size() > 0)
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
				if (message.size() > 0)
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
			result = MakeRequest(request, message);
			break;
		}
		if (message.size() > 0)
		{
			PrintMessage("\n" + message + "\n\n");
			message.clear();
		}

	} while (result && request != ERequestType::EXIT);

	PrintMessage("Goodbye\n");
}

bool CClient::Connect()
{
	is_connected = m_connector->ConnectToServer();
	return is_connected;
}

bool CClient::MakeRequest(ERequestType type, std::string& message)
{
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
	return false;
}

std::unique_ptr<CConnectorWrapper> CClient::InitConnector()
{
	return std::move(std::make_unique<CConnectorWrapper>(m_port, m_ip_address));
}

std::string CClient::RequestProcessesData()
{
	return m_connector->MakeRequest(EClientRequestType::PROCESSES_DATA);
}

std::string CClient::RequestDisksData()
{
	return m_connector->MakeRequest(EClientRequestType::DISKS_DATA);
}

std::string CClient::RequestAllData()
{
	return m_connector->MakeRequest(EClientRequestType::ALL_DATA);
}

void CClient::PrintMessage(const std::string& message) const
{
	m_consolePrinter->PrintMessage(message);
	m_filePrinter->PrintMessage(message);
}