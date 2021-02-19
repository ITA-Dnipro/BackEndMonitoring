#pragma once

#include "CClientView.h"
#include "CClientController.h"

class CClient
{
public:
	explicit CClient();
	~CClient()noexcept = default;

	void Execute();
	bool Init(const int arg_num, char** argvuments);

private:
	void PrintMessage(const std::string& message) const;

	const int c_num_arguments = 3;
	const int c_ip_address_num = 2;
	const int c_port_num = 1;

	std::string m_file_name;
	std::unique_ptr<CClientController> m_controller;
	std::unique_ptr<CClientView> m_consolePrinter;
	std::unique_ptr<CClientView> m_filePrinter;
	std::fstream m_log_file;
	std::fstream m_response_data;
};

