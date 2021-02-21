#pragma once
#include "CSocket.h"

class CSockAddress;

// This class allows user to connect to the server
class CConnector
{
public:
	explicit CConnector();
	CConnector(const CConnector&) = delete;
	CConnector(CConnector&&) noexcept = delete;
	~CConnector() noexcept;

	bool Initialize(const int port, const std::string& address);
	bool Connect() const;
	[[nodiscard]] CSocket& GetSocket();

private:
	std::unique_ptr<CSockAddress> InitSocketAddress(const std::string& ip_address,
		const int port);

	std::unique_ptr<CSockAddress> m_socket_address;
	CSocket m_socket_connector;
	bool m_is_initialized;
};