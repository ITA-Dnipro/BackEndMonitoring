#pragma once

class CConnectorWrapper;
enum class ERequestType;

class CClient
{
public:
	CClient(int port, const std::string& ip_address);
	bool Connect();
	~CClient();
	std::string MakeRequest(ERequestType type);
private:
	void InitLogger();
	std::unique_ptr<CConnectorWrapper> InitConnector();
	std::string GetProcessesData();
	std::string GetDisksData();
	std::string GetAllData();
	std::unique_ptr<CConnectorWrapper> m_connector;
	std::string m_ip_address;
	int m_port;
	bool is_connected;
};

