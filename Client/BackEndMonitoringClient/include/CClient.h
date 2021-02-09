#pragma once
#include "CClientView.h"

#include "Sockets/BackEndMonitoringSockets/include/CConnectorWrapper.h"
enum class ERequestType;

class CClient
{
public:
	explicit CClient();
	~CClient()noexcept = default;

	void Execute();
	bool Init(const int arg_num, char** argvuments);

private:
	const int c_num_arguments = 3;
	const int c_ip_address_num = 2;
	const int c_port_num = 1;

	bool Connect();
	bool MakeRequest(ERequestType type, std::string& message);
	std::unique_ptr<CConnectorWrapper> InitConnector();
	std::string RequestProcessesData();
	std::string RequestDisksData();
	std::string RequestAllData();
	void PrintMessage(const std::string& message) const;

	std::string m_ip_address;
	std::string m_file_name;
	std::unique_ptr<CConnectorWrapper> m_connector;
	std::unique_ptr<CClientView> m_consolePrinter;
	std::unique_ptr<CClientView> m_filePrinter;
	std::fstream m_log_file;
	std::fstream m_response_data;
	int m_port;
	bool is_connected;
};

