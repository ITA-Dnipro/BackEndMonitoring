#pragma once
#include "EEventType.h"
#include "CSocketWrapper.h"
#include "CDataReceiver.h"

enum class EClientRequestType;

// This class handles event form the server
class CServiceConnectionHandler
{
public:
	CServiceConnectionHandler() = delete;
	CServiceConnectionHandler(CDataReceiver json_data);
	CServiceConnectionHandler(const CServiceConnectionHandler&) = delete;
	CServiceConnectionHandler(CServiceConnectionHandler&&) noexcept = delete;
	~CServiceConnectionHandler() noexcept = default;

	bool HandleEvent(const int socket_fd, EEventType type);

private:
	const int c_client_disconnected = 10054;

	bool HandleRequestEvent(const int socket_fd);
	bool HandleResponseEvent(const int socket_fd, EClientRequestType type);
	bool HandleResponseExitEvent(const int socket_fd);
	void InitPeerStream();

	CDataReceiver m_json_data;
	std::unique_ptr<CSocketWrapper> m_p_peer_stream;
	bool m_can_receive_data;
};