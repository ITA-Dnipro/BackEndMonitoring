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

	void PrintMenu(bool is_table_mode, bool date_range_mode) const;
	EClientRequests GetRequest() const;
	void PrintMessage(const std::string& message) const;
	void PrintError() const;
	void SetIsWritingFile(bool status);
	bool GetIsWritingFile() const;
	std::string EnterDate() const;
	void PrintHelp() const;

private:
	
	std::ostream& m_file_stream;
	std::ostream& m_console_stream;
	std::istream& m_input_stream;
	bool m_should_write_file;
};

