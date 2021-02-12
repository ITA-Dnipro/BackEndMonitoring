#pragma once
#include "CSocket.h"

// This class allows user to connect to the server
class CConnector
{
public:
	CConnector() = delete;
	explicit CConnector(const int port, const std::string& address);
	CConnector(const CConnector&) = delete;
	CConnector(CConnector&&) noexcept = delete;
	~CConnector() noexcept;

	bool Initialize();
	bool Connect() const;
	[[nodiscard]] CSocket& GetSocket();

private:
	CSocket m_socket_connector;
};