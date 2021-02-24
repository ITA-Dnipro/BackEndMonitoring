#include "stdafx.h"

#include "CSocketWrapper.h"
#include "CLogger/include/Log.h"
#include "CSocket.h"
#include "GlobalVariable.h"
#include "ERequestType.h"
#include "EFrameError.h"

bool CSocketWrapper::Receive(const CSocket& client_socket, std::string& message)
{
	message.clear();
	int total_received_bytes = 0;
	int received_bytes = 0;
	char buff[GlobalVariable::c_max_buffer_size];
	std::string received_line;

	int total_msg_size = ReceiveHeader(client_socket);
	if (total_msg_size <= 0)
	{
		m_request_formatter.TryFormateRequest(message, 
			ERequestType::ERR, EFrameError::CONNECTION_PROBLEM);
		return false;
	}
	message.reserve(total_msg_size);
	received_line.reserve(total_msg_size);

	while(true)
	{
		received_bytes = recv(client_socket.GetSocketFD(), buff, 
			GlobalVariable::c_max_buffer_size, 0);

		if (received_bytes <= 0)
		{
			m_request_formatter.TryFormateRequest(message,
				ERequestType::ERR, EFrameError::CONNECTION_PROBLEM);
			CLOG_ERROR_WITH_PARAMS("Cannot receive data from the socket", 
				client_socket.GetSocketFD());
			return false;
		}
		received_line.append(buff, received_bytes);
		total_received_bytes += received_bytes;
		if (total_msg_size == total_received_bytes)
		{
			CLOG_DEBUG_WITH_PARAMS("We received bytes", total_received_bytes, 
				"socket", client_socket.GetSocketFD());
			message.append(received_line, 0U, received_line.size());
			CLOG_DEBUG_WITH_PARAMS("Size of the string", message.size());
			return true;
		}

	}
}

bool CSocketWrapper::Send(const CSocket& client_socket, const std::string& line)
{
	size_t line_length = line.length();
	size_t size_for_substring = line_length;
	std::string buff;
	size_t start_pos{ 0 };

	if(!SendHeaderSize(client_socket, line_length))
	{
		return false;
	}
	
	while (line_length > 0)
	{

		if (line_length >= GlobalVariable::c_max_buffer_size)
		{
			size_for_substring = GlobalVariable::c_max_buffer_size;
		}
		else
		{
			size_for_substring = line_length;
		}

		buff = line.substr(start_pos, size_for_substring);

		if (send(client_socket.GetSocketFD(), buff.c_str(), 
			static_cast<int>(buff.length()), 0) ==
			GlobalVariable::c_connection_error)
		{
			CLOG_ERROR_WITH_PARAMS("Cannot send data to the socket ", 
				client_socket.GetSocketFD());
			return false;
		}
		line_length -= size_for_substring;
		start_pos += size_for_substring;
		buff.clear();
	}
	CLOG_DEBUG_WITH_PARAMS("Send data to the socket ", client_socket.GetSocketFD());
	return true;
}

bool CSocketWrapper::SendHeaderSize(const CSocket& client_socket, size_t header_size)
{
	std::string msg_size = GlobalVariable::c_header_key_begin;
	msg_size += std::to_string(header_size);
	msg_size += GlobalVariable::c_header_key_end;
	
	if (send(client_socket.GetSocketFD(), msg_size.c_str(),
		static_cast<int>(msg_size.length()), 0) ==
		GlobalVariable::c_connection_error)
	{
		CLOG_ERROR_WITH_PARAMS("Cannot send header of the message to the socket ",
			client_socket.GetSocketFD());
		return false;
	}
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

	if (recv(client_socket.GetSocketFD(), &buff, 1, MSG_PEEK) == 
		GlobalVariable::c_connection_error)
	{
		return true;
	}
	return false;
}

int CSocketWrapper::ReceiveHeader(const CSocket& client_socket) const
{
	const int buff_size = 1;
	char buff[buff_size];
	std::string received_size;

	if(!ReceiveHeaderKey(client_socket, GlobalVariable::c_header_key_begin))
	{
		return 0;
	}
	
	while(true)
	{
		int received_bytes = recv(client_socket.GetSocketFD(), buff, 
			buff_size, MSG_PEEK);

		if (std::isdigit(buff[0]))
		{
			int received_bytes = recv(client_socket.GetSocketFD(), buff,
				buff_size, 0);
			received_size.append(buff, buff_size);
		}
		else
		{
			break;
		}
	}
	
	if (ReceiveHeaderKey(client_socket, GlobalVariable::c_header_key_end))
	{
		return ConvertDataToInt(received_size);
	}
	return 0;

}

bool CSocketWrapper::ReceiveHeaderKey(const CSocket& client_socket,
	const std::string& key) const
{
	const int buff_size = 1;
	char buff[buff_size];
	std::string received_key;
	while (true)
	{
		if(received_key.size() == key.size())
		{
			if(received_key.compare(key) == 0)
			{
				return true;
			}
			return false;
		}
		
		int received_bytes = recv(client_socket.GetSocketFD(), buff, 
			buff_size, 0);

		received_key.append(buff, buff_size);
	}
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
