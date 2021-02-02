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
	~CConnector() noexcept = default;

	bool Connect();
	[[nodiscard]] int GetSocketFD() const;
private:
	[[nodiscard]] std::unique_ptr<CSocket> InitSocketConnector(const int port,
		const std::string& ip_address);

	std::unique_ptr<CSocket> m_p_socket_connector;
};