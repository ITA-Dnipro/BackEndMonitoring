#pragma once
#include "CServiceHandler.h"
#include "CSocketWrapper.h"
#include "CClientConnectionHandler.h"
#include "CServerResponseHolder.h"
#include "EClientRequestType.h"

class CConnector;

// This class is the window for the user to send requests to the server and 
// get responses from it
class CConnectorWrapper
{
public:
	CConnectorWrapper() = delete;
	CConnectorWrapper(int port, const std::string& ip_address);
	CConnectorWrapper(const CConnectorWrapper&) = delete;
	CConnectorWrapper(CConnectorWrapper&&) noexcept = delete;
	~CConnectorWrapper();

	bool MakeRequest(EClientRequestType r_type) const;
	bool ConnectToServer() const;
	void Exit();

private:
	[[nodiscard]] std::unique_ptr<CConnector> InitConnector(int port,
		const std::string& ip_address);
	[[nodiscard]] std::unique_ptr<CClientConnectionHandler> InitClientHandler();

	std::string m_address;
	std::unique_ptr<CClientConnectionHandler> m_p_client_handler;
	std::unique_ptr<CConnector> m_p_connector;
	CServerResponseHolder m_response_holder;
	int m_port;
};