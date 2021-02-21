#pragma once
#include "EEventType.h"
#include "CDataProvider.h"
#include "CRequestHandler.h"

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
	bool HandleRequestEvent(const CSocket& client_socket);
	bool HandleResponseEvent(const CSocket& client_socket, 
		const std::string& response_message);
	bool HandleWrongRequestEvent(const CSocket& client_socket);
	bool IsEqualStrings(const std::string& first_str, 
		const std::string& second_str) const;
	void InitPeerStream();
	EClientRequestType ParseMessageType(const std::string& message) const;

	CRequestHandler m_request_handler;
	std::unique_ptr<CSocketWrapper> m_p_peer_stream;
};