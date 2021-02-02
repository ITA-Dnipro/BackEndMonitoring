#pragma once
#include "CServiceHandler.h"
#include "CSocketWrapper.h"
#include "CServerResponseHolder.h"

// This class handles event form the user
class CClientConnectionHandler : public CServiceHandler
{
public:
	explicit CClientConnectionHandler();
	CClientConnectionHandler(const CClientConnectionHandler&) = delete;
	CClientConnectionHandler(CClientConnectionHandler&&) noexcept = delete;
	~CClientConnectionHandler() noexcept = default;

	bool HandleEvent(const int socket, EventType type) override;

private:
	bool HandleRequestEvent(const int socket, EventType type);
	bool HandleResponseEvent(const int socket);
	bool HandleExitEvent(const int socket);
	[[nodiscard]] std::unique_ptr<CSocketWrapper> InitClientStream();

	std::unique_ptr<CSocketWrapper> m_p_client_stream;
	CServerResponseHolder m_response_holder;
};
