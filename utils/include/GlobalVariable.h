#pragma once
#include <string>

namespace GlobalVariable
{
	const std::string c_header_key_begin = "^%$^";		// Cannot contain digits!!!
	const std::string c_header_key_end = "^&#^";		// Cannot contain digits!!!
	static const int c_max_buffer_size = 500u;
	const int c_connection_error = -1;
	constexpr int c_error_socket = -1;
	constexpr int c_invalid_socket = 0;
	constexpr int c_success = 0;
	constexpr int c_max_valid_socket = 65535;
	const std::string c_request_error = "ERROR";
	const std::string c_lost_request = "REQUEST LOST";
	const std::string c_connection_problem = "-1";
	const std::string c_exit_message = "EXIT";

	static const std::string c_request_key_id = "id";
	static const std::string c_request_key_req_typ = "request_type";
	static const std::string c_request_key_spec = "special";
	static const std::string c_request_key_duration = "duration";
	static const std::string c_request_format_default = "%d.%m.%Y %X";
	static const std::string c_response_data = "data";
	static const std::string c_frame_error = "error";

}