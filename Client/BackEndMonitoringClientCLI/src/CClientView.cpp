#include "stdafx.h"

#include "CStringCleaner.h"
#include "CClientView.h"

CClientView::CClientView(std::ostream& out_console, std::ostream& out_file, 
	std::istream& in) : m_console_stream(out_console),
	m_file_stream(out_file), m_input_stream(in),
	m_should_write_file(true)
{ }

void CClientView::PrintMenu(bool show_response_mode, bool date_range_mode) const
{
	m_console_stream << "\n\n\t\t\t\t\tMenu\n" << std::endl
		<< "\t\x1b[1;32m[\x1b[1;31mdrives data\x1b[1;32m]\x1b[0m      "
				<< "current info about logical drives\n"
	
		<< "\t\x1b[1;32m[\x1b[1;31mprocesses data\x1b[1;32m]\x1b[0m   "
				<< "current info about running processes\n"
	
		<< "\t\x1b[1;32m[\x1b[1;31mall data\x1b[1;32m]\x1b[0m         "
				<< "all current info about the server state\n"
	
		<< "\t\x1b[1;32m[\x1b[1;31mnon stop\x1b[1;32m]\x1b[0m         "
				<< "make requests to the server non-stop \x1b[1;33m(all data)\x1b[0m\n\n"
	
		<< "\t\x1b[1;32m[\x1b[1;31mdate mode\x1b[1;32m]\x1b[0m        " << "change request mode \x1b[1;33m(current: \x1b[1;36m"
				<< (date_range_mode ? "request by date range" : "last info") << "\x1b[1;33m)\x1b[0m\n"
	
		<< "\t\x1b[1;32m[\x1b[1;31mfile\x1b[1;32m]\x1b[0m		   save response to file \x1b[1;33m(current: \x1b[1;36m"
				<< (m_should_write_file ? "enabled" : "disabled") << "\x1b[1;33m)\x1b[0m\n"
	
		<< "\t\x1b[1;32m[\x1b[1;31mchange view\x1b[1;32m]\x1b[0m      "
				<< "change printing data mode \x1b[1;33m(current: \x1b[1;36m"
				<< (show_response_mode ? "as json" : "as table") << "\x1b[1;33m)\x1b[0m\n"
	
		<< "\t\x1b[1;32m[\x1b[1;31mcls\x1b[1;32m]\x1b[0m              clean screen\n"
	
		<< "\t\x1b[1;32m[\x1b[1;31mexit\x1b[1;32m]\x1b[0m             exit\n" << std::endl;

}

EClientRequests CClientView::GetRequest() const
{
	std::string choice_str;

	std::getline(m_input_stream, choice_str);
	{
		CStringCleaner choice(std::move(choice_str));
		choice_str = choice.GetTrimmedLowercaseString();
	}

	for(size_t i = 0u; i < static_cast<size_t>(EClientRequests::COUNT); ++i)
	{
		if(choice_str.compare(g_c_client_requests[i]) == 0)
		{
			return static_cast<EClientRequests>(i);
		}
	}
	
	return EClientRequests::ERR;
}

std::string CClientView::EnterPort() const
{
	std::string port;
	m_console_stream << "Please, enter port for connection (or \"exit\" to exit):\n";
	std::getline(m_input_stream, port);

	return port;
}

std::string CClientView::EnterIpAddress() const
{
	std::string ip_address;
	m_console_stream << "Please, enter ip address for connection (or \"exit\" to exit):\n";
	std::getline(m_input_stream, ip_address);

	return ip_address;
}

void CClientView::PrintMessage(const std::string& result) const
{
	m_console_stream << result;
	if(m_should_write_file)
	{
		m_file_stream << result << '\n';
	}
}

void CClientView::PrintError() const
{
	std::string err_message = "Sorry, you entered something wrong :(\n";
	m_console_stream << err_message;
	if (m_should_write_file)
	{
		m_file_stream << err_message;
	}
}

void CClientView::PrintSuccessConnection() const
{
	std::string msg = "\n\n\n\n\n\t\t\t\tSuccessfully connected to the server!\n";
	m_console_stream << msg;
	if (m_should_write_file)
	{
		m_file_stream << msg;
	}
}

void CClientView::PrintErrorConnection() const
{
	std::string err_message = "\n\n\n\n\n\t\t\t\tYou passed the wrong networking parameters, please, try again!\n";
	m_console_stream << err_message;
	if (m_should_write_file)
	{
		m_file_stream << err_message;
	}
}

bool CClientView::GetIsWritingFile() const
{
	return m_should_write_file;
}

void CClientView::SetIsWritingFile(bool status)
{
	m_should_write_file = status;
}
