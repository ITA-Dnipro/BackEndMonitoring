#include "stdafx.h"

#include "ERequestType.h"

#include "CStringCleaner.h"

#include "CClientView.h"

CClientView::CClientView(std::ostream& out, std::istream& in) :
	m_output_stream(out), m_input_stream(in)
{ }

void CClientView::PrintMenu()
{
	m_output_stream << "\t\tMenu" << std::endl
		<< "\t[drives data] : get current status about logical drives of the server\n"
		<< "\t[processes data] - get current status about running processes of the server server\n"
		<< "\t[all data] - get current status about the server\n"
		<< "\t[cycle] - run 20 iterations of [all data]\n"
		<< "\t[exit] - exit" << std::endl;

}

ERequestType CClientView::GetRequest()
{
	std::string choice_str;
	std::getline(m_input_stream, choice_str);
	{
		CStringCleaner choice(std::move(choice_str));
		choice_str = choice.GetTrimmedLowercaseString();
	}

	if (choice_str == "drives data")
	{
		return ERequestType::DISKS_DATA;
	}
	else if (choice_str == "processes data")
	{
		return ERequestType::PROCESSES_DATA;
	}
	else if (choice_str == "all data")
	{
		return ERequestType::ALL_DATA;
	}
	else if (choice_str == "cycle")
	{
		return ERequestType::ALL_DATA_CYCLE;
	}
	else if (choice_str == "exit")
	{
		return ERequestType::EXIT;
	}

	return ERequestType::ERR;
}

void CClientView::PrintResult(const std::string& result)
{
	m_output_stream << result << '\n';
}

void CClientView::PrintError()
{
	m_output_stream << "Sorry, you entered something wrong :(\n";
}

void CClientView::PrintGoodbye()
{
	m_output_stream << "Goodbye\n";
}

