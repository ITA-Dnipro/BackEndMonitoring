#include "stdafx.h"

#include "CSocketWrapper.h"
#include "CLogger/include/Log.h"

bool CSocketWrapper::Receive(const int socket_fd, std::string& message)
{
	message.clear();
	int total_received_bytes = 0;
	int received_bytes = 0;
	int current_message_size = 0;
	char* buff = new char[c_max_buffer_size];
	std::string received_line;

	int total_msg_size = GetSizeFromHeader(socket_fd);
	if (total_msg_size == 0)
	{
		message = "-1";
		return false;
	}
	message.reserve(total_msg_size);
	received_line.reserve(total_msg_size);

	if (total_msg_size >= c_max_buffer_size)
	{
		current_message_size = GetSizeFromHeader(socket_fd);
	}
	else
	{
		current_message_size = total_msg_size;
	}

	while(current_message_size > 0)
	{
		received_bytes = recv(socket_fd, buff, current_message_size, 0);

		if (received_bytes == -1)
		{
			message = "-1";
			return false;
		}
		received_line.append(buff, current_message_size);
		total_received_bytes += received_bytes;
		if (total_msg_size == total_received_bytes)
		{
			CLOG_DEBUG_WITH_PARAMS("We received bytes", total_received_bytes, 
				"socket", socket_fd);
			message.append(received_line, 0U, received_line.size());
			CLOG_DEBUG_WITH_PARAMS("Size of the string", message.size());
			delete[] buff;
			return true;
		}
		current_message_size = GetSizeFromHeader(socket_fd);

	}
	CLOG_ERROR_WITH_PARAMS("Error receiving data, we should receive/we receive/broken message/socket descriptor", 
		total_msg_size, total_received_bytes, message, socket_fd);
	delete[] buff;

	return false;
}

bool CSocketWrapper::Send(const int socket_fd, const std::string& line)
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

		if (send(socket_fd, buff.c_str(), static_cast<int>(buff.length()), 0) == 
			c_connection_error)
		{
			return false;
		}
		line_length -= size_for_substring;
		start_pos += size_for_substring;
		buff.clear();
		temp_line.clear();
	}
	CLOG_DEBUG_WITH_PARAMS("Send data to the socket ", socket_fd);
	return true;
}

bool CSocketWrapper::CanReceiveData(const int socket_fd) const
{
	char buff;

	if (recv(socket_fd, &buff, 1, MSG_PEEK) > 0)
	{
		return true;
	}
	return false;
}

bool CSocketWrapper::IsErrorOccured(const int socket_fd) const
{
	char buff;

	if (recv(socket_fd, &buff, 1, MSG_PEEK) == c_connection_error)
	{
		return true;
	}
	return false;
}

std::string CSocketWrapper::CreateHeader(const int size)
{
	std::string header = "@";
	header += std::to_string(size);
	header += "$";
	return header;
}

int CSocketWrapper::GetSizeFromHeader(const int socket_fd) const
{
	std::string header_data;
	char* buff = new char[1];

	while (true)
	{
		if (recv(socket_fd, buff, 1, 0) == c_connection_error)
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
