#pragma once
#include "EEventType.h"
#include "CDataProvider.h"

class CSocketWrapper;
class CSocket;
enum class EClientRequestType;

// This class handles event form the server
class CServiceConnectionHandler
{
public:
	CServiceConnectionHandler() = delete;
	CServiceConnectionHandler(CDataProvider json_data);
	CServiceConnectionHandler(const CServiceConnectionHandler&) = delete;
	CServiceConnectionHandler(CServiceConnectionHandler&&) noexcept = delete;
	~CServiceConnectionHandler() noexcept = default;

	bool HandleEvent(const CSocket& client, EEventType event_type);

private:
	bool HandleRequestEvent(const CSocket& client_socket);
	bool HandleResponseEvent(const CSocket& client_socket, EClientRequestType type);
	bool HandleWrongRequestEvent(const CSocket& client_socket);
	bool IsEqualStrings(const std::string& first_str, 
		const std::string& second_str) const;
	void InitPeerStream();
	EClientRequestType ParseMessageType(const std::string& message) const;

	CDataProvider m_json_data;
	std::unique_ptr<CSocketWrapper> m_p_peer_stream;
};