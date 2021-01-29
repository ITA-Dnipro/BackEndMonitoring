#pragma once
#pragma once

class CConnectorWrapper;

class CClient
{
public:
	CClient(int port, const std::string& ip_address);
	~CClient();
	void MakeRequest();
private:
	void InitLogger();
	std::unique_ptr<CConnectorWrapper> InitConnector();
	bool GetRequestConfirmation();

	std::unique_ptr<CConnectorWrapper> m_connector;
	std::string m_ip_address;
	int m_port;

};

