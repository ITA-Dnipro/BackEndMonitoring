#pragma once
#include "EEventType.h"
#include "CSocketWrapper.h"

// This class handles event form the user
class CClientConnectionHandler
{
public:
	explicit CClientConnectionHandler();
	CClientConnectionHandler(const CClientConnectionHandler&) = delete;
	CClientConnectionHandler(CClientConnectionHandler&&) noexcept = delete;
	~CClientConnectionHandler() noexcept = default;

	bool HandleEvent(const int socket, EEventType type, std::string& message);

private:
	bool HandleRequestEvent(const int socket, EEventType type);
	bool HandleResponseEvent(const int socket, std::string& message);
	bool HandleExitEvent(const int socket);
	bool HandleDataReceivedEvent(const int socket);
	bool HandleLostRequestEvent(const int socket, std::string& message);
	bool SendRequestToServer(const int socket, const std::string& message);
	std::string ConvertRequestToString(EEventType type) const;
	[[nodiscard]] std::unique_ptr<CSocketWrapper> InitClientStream();

	std::unique_ptr<CSocketWrapper> m_p_client_stream;
	EEventType m_current_request;
};
