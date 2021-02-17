#pragma once
#include "EEventType.h"
#include "CSocketWrapper.h"

class CSocket;

// This class handles event form the user
class CClientConnectionHandler
{
public:
	explicit CClientConnectionHandler();
	CClientConnectionHandler(const CClientConnectionHandler&) = delete;
	CClientConnectionHandler(CClientConnectionHandler&&) noexcept = delete;
	~CClientConnectionHandler() noexcept = default;

	bool HandleEvent(const CSocket& client_socket, EEventType type, 
		std::string& message);

private:
	bool HandleRequestEvent(const CSocket& client_socket, EEventType type) const;
	bool HandleResponseEvent(const CSocket& client_socket, std::string& message);
	bool HandleExitEvent(const CSocket& client_socket);
	bool HandleLostRequestEvent(const CSocket& client_socket, 
		std::string& message);
	bool SendRequestToServer(const CSocket& client_socket, 
		const std::string& message) const;
	std::string ConvertRequestToString(EEventType type) const;
	[[nodiscard]] std::unique_ptr<CSocketWrapper> InitClientStream();

	std::unique_ptr<CSocketWrapper> m_p_client_stream;
	EEventType m_current_request;
};
