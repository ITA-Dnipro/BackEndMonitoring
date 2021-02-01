#include "Sockets/BackEndMonitoringSockets/include/stdafx.h"

#include "CSocketWrapper.h"
#include "Log.h"

CSocketWrapper::CSocketWrapper()
{ }

std::string CSocketWrapper::Receive(const int socket)
{
	std::string received_line;

	int msg_size = GetSizeFromHeader(socket);
	//CLOG_DEBUG_WITH_PARAMS("Receive data from the socket ", socket, ", header size ", msg_size);
	if (msg_size == 0)
	{
		return "-1";
	}

	char* buff = new char[msg_size];

	int received_bytes = recv(socket, buff, msg_size, NULL);

	received_line.clear();
	received_line.append(buff, msg_size);

	if (!IsAllDataReceived(msg_size, received_line.length()))
	{
		return "Part of the data is lost";
	}

	return received_line;
}

bool CSocketWrapper::Send(const int socket, const std::string& line)
{
	std::string buff = CreateHeader(static_cast<int>(line.length()));
	buff += line;
	//CLOG_DEBUG_WITH_PARAMS("Send data to the socket ", socket, ", size ", buff.length());
	if (send(socket, buff.c_str(), static_cast<int>(buff.length()), 0) == CONNECTION_ERROR)
	{
		return false;
	}
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

std::string CSocketWrapper::CreateHeader(const int size)
{
	std::string header = "@";
	header += std::to_string(size);
	header += "$";
	return header;
}

int CSocketWrapper::GetSizeFromHeader(const int socket) const
{
	std::string header_data;
	char* buff = new char[1];

	while (true)
	{
		if (recv(socket, buff, 1, NULL) == CONNECTION_ERROR)
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

