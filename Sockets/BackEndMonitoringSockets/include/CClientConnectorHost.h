#pragma once
#include "EClientRequestType.h"
#include "CClientConnectionHandler.h"

class CConnector;

// This class is the window for the user to send requests to the server and 
// get responses from it
class CClientConnectorHost
{
public:
	CClientConnectorHost();
	CClientConnectorHost(const CClientConnectorHost&) = delete;
	CClientConnectorHost(CClientConnectorHost&&) noexcept = delete;
	~CClientConnectorHost();

	bool Initialize(const int port, const std::string& ip_address);
	bool ConnectToServer() const;
	[[nodiscard]] std::string MakeRequest(EClientRequestType r_type) const;
	bool Exit() const;

private:
	[[nodiscard]] std::unique_ptr<CClientConnectionHandler> InitClientHandler();
	std::unique_ptr<CConnector> InitConnector();

	std::unique_ptr<CClientConnectionHandler> m_p_client_handler;
	std::unique_ptr<CConnector> m_connector;
	bool m_is_initialized;
};