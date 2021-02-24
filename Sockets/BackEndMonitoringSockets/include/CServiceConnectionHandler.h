#pragma once
#include "EEventType.h"
#include "CRequestHandler.h"
#include "CRequestFrame.h"

class CSocketWrapper;
class CSocket;
enum class EClientRequestType;

// This class handles event form the server
class CServiceConnectionHandler
{
public:
	CServiceConnectionHandler() = delete;
	CServiceConnectionHandler(CRequestHandler json_data);
	CServiceConnectionHandler(const CServiceConnectionHandler&) = delete;
	CServiceConnectionHandler(CServiceConnectionHandler&&) noexcept = delete;
	~CServiceConnectionHandler() noexcept = default;

	bool HandleEvent(const CSocket& client, EEventType event_type);

private:
	bool HandleRequestEvent(const CSocket& client);
	bool HandleResponseEvent(const CSocket& client_socket, 
		const std::string& response_message);
	void InitPeerStream();

	CRequestHandler m_request_handler;
	CRequestFrame m_request_formatter;
	std::unique_ptr<CSocketWrapper> m_p_peer_stream;
};