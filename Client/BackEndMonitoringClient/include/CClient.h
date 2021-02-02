#pragma once

class CConnectorWrapper;
enum class ERequestType;

class CClient
{
public:
	CClient(int port, const std::string& ip_address);
	bool Connect();
	~CClient();
	bool MakeRequest(ERequestType type);
private:
	void InitLogger();
	std::unique_ptr<CConnectorWrapper> InitConnector();
	bool RequestProcessesData();
	bool RequestDisksData();
	bool RequestAllData();
	std::unique_ptr<CConnectorWrapper> m_connector;
	std::string m_ip_address;
	int m_port;
	bool is_connected;
};

