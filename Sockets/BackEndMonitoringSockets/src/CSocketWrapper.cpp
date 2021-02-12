#include "stdafx.h"

#include "CSocketWrapper.h"
#include "CLogger/include/Log.h"
#include "CSocket.h"

bool CSocketWrapper::Receive(const CSocket& client_socket, std::string& message)
{
	message.clear();
	int total_received_bytes = 0;
	int received_bytes = 0;
	int current_message_size = 0;
	char buff[c_max_buffer_size];
	std::string received_line;

	int total_msg_size = GetSizeFromHeader(client_socket);
	if (total_msg_size == 0)
	{
		message = "-1";
		return false;
	}
	message.reserve(total_msg_size);
	received_line.reserve(total_msg_size);

	if (total_msg_size >= c_max_buffer_size)
	{
		current_message_size = GetSizeFromHeader(client_socket);
	}
	else
	{
		current_message_size = total_msg_size;
	}

	while(current_message_size > 0)
	{
		received_bytes = recv(client_socket.GetSocketFD(), buff, current_message_size, 0);

		if (received_bytes <= 0)
		{
			message = "-1";
			return false;
		}
		received_line.append(buff, current_message_size);
		total_received_bytes += received_bytes;
		if (total_msg_size == total_received_bytes)
		{
			CLOG_DEBUG_WITH_PARAMS("We received bytes", total_received_bytes, 
				"socket", client_socket.GetSocketFD());
			message.append(received_line, 0U, received_line.size());
			CLOG_DEBUG_WITH_PARAMS("Size of the string", message.size());
			return true;
		}
		current_message_size = GetSizeFromHeader(client_socket);

	}
	CLOG_ERROR_WITH_PARAMS("Error receiving data, we should receive/we receive/broken message/socket descriptor", 
		total_msg_size, total_received_bytes, message, client_socket.GetSocketFD());

	return false;
}

bool CSocketWrapper::Send(const CSocket& client_socket, const std::string& line)
{
	size_t line_length = line.length();
	size_t size_for_substring = line_length;
	std::string temp_line;
	std::string buff;
	size_t start_pos{ 0 };

	if (line_length >= c_max_buffer_size)
	{
		buff = CreateHeader(static_cast<int>(line_length));
	}

	while (line_length > 0)
	{

		if (line_length >= c_max_buffer_size)
		{
			size_for_substring = c_max_buffer_size;
		}
		else
		{
			size_for_substring = line_length;
		}

		temp_line = line.substr(start_pos, size_for_substring);

		buff += CreateHeader(static_cast<int>(temp_line.length()));
		buff += temp_line;

		if (send(client_socket.GetSocketFD(), buff.c_str(), static_cast<int>(buff.length()), 0) ==
			c_connection_error)
		{
			return false;
		}
		line_length -= size_for_substring;
		start_pos += size_for_substring;
		buff.clear();
		temp_line.clear();
	}
	CLOG_DEBUG_WITH_PARAMS("Send data to the socket ", client_socket.GetSocketFD());
	return true;
}

bool CSocketWrapper::CanReceiveData(const CSocket& client_socket) const
{
	char buff;

	if (recv(client_socket.GetSocketFD(), &buff, 1, MSG_PEEK) > 0)
	{
		return true;
	}
	return false;
}

bool CSocketWrapper::IsErrorOccurred(const CSocket& client_socket) const
{
	char buff;

	if (recv(client_socket.GetSocketFD(), &buff, 1, MSG_PEEK) == c_connection_error)
	{
		return true;
	}
	return false;
}

std::string CSocketWrapper::CreateHeader(const int size) const
{
	std::string header = "@";
	header += std::to_string(size);
	header += "$";
	return header;
}

int CSocketWrapper::GetSizeFromHeader(const CSocket& client_socket) const
{
	std::string header_data;
	char* buff = new char[1];

	while (true)
	{
		int received_bytes = recv(client_socket.GetSocketFD(), buff, 1, 0);
		if (received_bytes <= 0)
		{
			return 0;
		}
		if (buff[0] == '@')
		{
			continue;
		}
		else if (buff[0] == '$')
		{
			break;
		}
		header_data += buff[0];
	}
	delete[] buff;

	return ConvertDataToInt(header_data);
}

bool CSocketWrapper::IsAllDataReceived(int msg_size,
	int received_msg_size) const
{
	return msg_size == received_msg_size;
}

int CSocketWrapper::ConvertDataToInt(const std::string& data) const
{
	int msg_size = 0;

	try
	{
		msg_size = stoi(data);
	}
	catch (std::out_of_range)
	{
		msg_size = 0;
	}
	catch (std::invalid_argument)
	{
		msg_size = 0;
	}

	return msg_size;
}
