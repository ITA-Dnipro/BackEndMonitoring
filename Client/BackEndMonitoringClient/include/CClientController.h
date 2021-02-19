#pragma once

#include "Sockets/BackEndMonitoringSockets/include/CClientConnectorHost.h"
enum class ERequestType;

class CClientController
{
public:
	CClientController();

	bool Connect();
	bool MakeRequest(ERequestType type, std::string& message);
	bool InitHost(const int port, const std::string& ip_address);

private:
	std::string RequestProcessesData();
	std::string RequestDisksData();
	std::string RequestAllData();

	std::string m_ip_address;
	std::unique_ptr<CClientConnectorHost> m_connector;
	int m_port;
	bool is_connected;
};

