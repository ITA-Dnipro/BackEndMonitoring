#pragma once

#include "Sockets/BackEndMonitoringSockets/include/CClientConnectorHost.h"
enum class ERequestType;

class CClientController
{
public:
	CClientController();

	bool Connect();
	bool MakeRequest(std::string& message, ERequestType req_typ,
		ERequestRangeSpecification spec_typ,
		const std::string& date_of_start = "",
		const std::string& date_of_end = "");
	bool InitHost(const int port, const std::string& ip_address);

private:
	std::string m_ip_address;
	std::unique_ptr<CClientConnectorHost> m_connector;
	int m_port;
	bool is_connected;
};

