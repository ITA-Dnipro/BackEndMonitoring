#pragma once
#include "CClientView.h"

#include "Sockets/BackEndMonitoringSockets/include/CClientConnectorHost.h"
enum class ERequestType;

class CClient
{
public:
	explicit CClient();
	~CClient()noexcept = default;

	void Execute();
	bool Init(const int arg_num, char** arguments);

private:
	const int c_num_arguments = 3;
	const int c_ip_address_num = 2;
	const int c_port_num = 1;

	bool Connect();
	bool MakeRequest(std::string& message, ERequestType req_typ,
		ERequestRangeSpecification spec_typ,
		const std::string& date_of_start = "", 
		const std::string& date_of_end = "");
	bool InitHost(const int port, const std::string& ip_address);
	void PrintMessage(const std::string& message) const;

	std::string m_ip_address;
	std::string m_file_name;
	std::unique_ptr<CClientConnectorHost> m_connector;
	std::unique_ptr<CClientView> m_consolePrinter;
	std::unique_ptr<CClientView> m_filePrinter;
	std::fstream m_log_file;
	std::fstream m_client_stream;
	int m_port;
	bool is_connected;
};

