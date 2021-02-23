#pragma once

#include "CClientView.h"
#include "CClientController.h"
#include "CResponseAdapter.h"

class CClient
{
public:
	explicit CClient();
	~CClient()noexcept = default;

	void Execute(const int arg_num, char** arguments);

private:
	const int c_num_arguments = 3;
	const int c_ip_address_num = 2;
	const int c_port_num = 1;
	
	void Init();
	bool EstablishConnectionWithServer(const int arg_num, char** arguments);
	bool Connect(const int port, const std::string& ip_address);
	bool MakeRequest(ERequestType req_type) const;
	bool MakeCycleOfRequests() const;
	bool MakeNonStopRequests() const;
	
	std::string m_file_name;
	std::unique_ptr<CClientController> m_controller;
	std::unique_ptr<CClientView> m_printer;
	CResponseAdapter resp_converter;
	std::fstream m_log_file;
	std::fstream m_client_stream;
	bool is_connected;
	bool m_is_initialized;
	bool m_show_as_table;
	bool m_is_date_range_mode;
};
