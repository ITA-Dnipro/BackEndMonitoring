#pragma once

#include "EClientRequests.h"

class CClientView
{
public:
	CClientView(std::ostream& out_console, std::ostream& out_file, 
		std::istream& in);
	CClientView(const CClientView&) = delete;
	CClientView(CClientView&&) = delete;
	~CClientView() noexcept = default;

	void PrintMenu(bool show_response_mode, bool date_range_mode) const;
	EClientRequests GetRequest() const;
	std::string EnterPort() const;
	std::string EnterIpAddress() const;
	void PrintMessage(const std::string& result) const;
	void PrintError() const;
	void PrintSuccessConnection() const;
	void PrintErrorConnection() const;
	void SetIsWritingFile(bool status);
	bool GetIsWritingFile() const;

private:
	
	std::ostream& m_file_stream;
	std::ostream& m_console_stream;
	std::istream& m_input_stream;
	bool m_should_write_file;
};

