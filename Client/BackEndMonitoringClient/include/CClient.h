#pragma once
#include "CClientView.h"

#include "Sockets/BackEndMonitoringSockets/include/CConnectorWrapper.h"
enum class ERequestType;

class CClient
{
public:
	explicit CClient(int port, const std::string& ip_address, 
		std::string file_name);
	~CClient();

	void Execute();

private:
	bool Connect();
	bool MakeRequest(ERequestType type, std::string& message);
	void Init(std::string file_name);
	void InitLogger();
	std::unique_ptr<CConnectorWrapper> InitConnector();
	std::string RequestProcessesData();
	std::string RequestDisksData();
	std::string RequestAllData();
	void PrintMessage(const std::string& message) const;

	std::string m_ip_address;
	std::unique_ptr<CConnectorWrapper> m_connector;
	std::unique_ptr<CClientView> m_consolePrinter;
	std::unique_ptr<CClientView> m_filePrinter;
	std::fstream m_log_file;
	std::fstream m_response_data;
	int m_port;
	bool is_connected;
};

