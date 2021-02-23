#pragma once
#include "CSocketWrapper.h"
#include "ERequestRangeSpecification.h"
#include "CRequestFrame.h"
#include "CResponseHandler.h"

class CSocket;

// This class handles event form the user
class CClientConnectionHandler
{
public:
	explicit CClientConnectionHandler();
	CClientConnectionHandler(const CClientConnectionHandler&) = delete;
	CClientConnectionHandler(CClientConnectionHandler&&) noexcept = delete;
	~CClientConnectionHandler() noexcept = default;

	bool HandleEvent(const CSocket& client_socket, std::string& message, 
		ERequestType req_typ, EFrameError error = EFrameError::NONE, 
		ERequestRangeSpecification spec_typ = ERequestRangeSpecification::LAST_DATA,
		const std::string& date_of_start = "", 
		const std::string& date_of_end = "");
	

private:
	bool HandleRequestEvent(const CSocket& client_socket, 
		const std::string& request) const;
	bool HandleResponseEvent(const CSocket& client_socket, std::string& message);
	bool HandleExitEvent(const CSocket& client_socket);
	bool HandleLostRequestEvent(const CSocket& client_socket, 
		std::string& message);
	bool SendRequestToServer(const CSocket& client_socket, 
		const std::string& message) const;
	[[nodiscard]] std::unique_ptr<CSocketWrapper> InitClientStream();

	CResponseHandler m_response_handler;
	CRequestFrame m_request_formatter;
	nlohmann::json json_format;
	std::string m_current_request;
	std::unique_ptr<CSocketWrapper> m_p_client_stream;
};
