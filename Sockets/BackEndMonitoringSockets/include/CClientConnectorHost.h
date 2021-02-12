#pragma once
#include "EClientRequestType.h"
#include "CClientConnectionHandler.h"

class CConnector;

// This class is the window for the user to send requests to the server and 
// get responses from it
class CClientConnectorHost
{
public:
	CClientConnectorHost() = delete;
	CClientConnectorHost(const int port, const std::string& ip_address);
	CClientConnectorHost(const CClientConnectorHost&) = delete;
	CClientConnectorHost(CClientConnectorHost&&) noexcept = delete;
	~CClientConnectorHost();

	bool ConnectToServer() const;
	//int GetClientSocket() const;
	[[nodiscard]] std::string MakeRequest(EClientRequestType r_type) const;
	bool Exit() const;

private:
	const int c_equal = 0;
	
	[[nodiscard]] std::unique_ptr<CClientConnectionHandler> InitClientHandler();
	std::unique_ptr<CConnector> InitConnector(const int port, 
		const std::string& ip_address);

	std::unique_ptr<CClientConnectionHandler> m_p_client_handler;
	std::unique_ptr<CConnector> m_connector;
};