#include "stdafx.h"
#include "CXMLParser.h"


bool CXMLParser::Initialize(const std::string& path_to_configuration_file)
{
	p_file_ = std::move(std::make_unique<pugi::xml_document>());
	return p_file_->load_file(path_to_configuration_file.c_str());
}

bool CXMLParser::IsFileInitialized() const
{
	if (nullptr == p_file_)
	{
		// write to logger that xml file isn't initialized
		return false;
	}

	return true;
}

void CXMLParser::ReadConfigFromFile()
{

	GetServerConfigurationFromFile();
	GetComunicationConfigurationFromFile();
	GetLoggingConfigurationFromFile();
	GetTimeConfigurationFromFile();
	GetThreadPoolConfigurationFromFile();
	GetHDDInfoConfigurationFromFile();
	GetProcessInfoConfigurationFromFile();

}

void CXMLParser::GetServerConfigurationFromFile()
{

	std::string tmp_string;
	int tmp_int = 0;

	if (TryToGetStringData("//root/Server/servername", tmp_string))
		server_.server_name = tmp_string != "" ? tmp_string : server_.server_name;

	if (TryToGetStringData("//root/Server/serverdisplayname", tmp_string))
		server_.server_displayname = tmp_string != "" ? tmp_string : server_.server_displayname;


	if (TryToGetStringData("//root/Server/listenerport", tmp_string))
		server_.listener_port = TryToConvertToInt(tmp_string, tmp_int) ? tmp_int : server_.listener_port;

	if (TryToGetStringData("//root/Server/ipaddress", tmp_string))
		server_.ip_address = tmp_string != "" ? tmp_string : server_.ip_address;

}

void CXMLParser::GetComunicationConfigurationFromFile()
{

	std::string tmp_string;
	int tmp_int = 0;

	if (TryToGetStringData("//root/communicationsettings/blocking", tmp_string))
		comunication_settings_.blocking = TryToConvertToInt(tmp_string, tmp_int) ? tmp_int : comunication_settings_.blocking;

	if (TryToGetStringData("//root/communicationsettings/socket_timeout", tmp_string))
		comunication_settings_.socket_timeout = TryToConvertToInt(tmp_string, tmp_int) ? tmp_int : comunication_settings_.socket_timeout;

}

void CXMLParser::GetLoggingConfigurationFromFile()
{
	std::string tmp_string;
	int tmp_int = 0;

	if (TryToGetStringData("//root/logging/filename", tmp_string))
		logging_.file_name = tmp_string != "" ? tmp_string : logging_.file_name;

	if (TryToGetStringData("//root/logging/LogLevel", tmp_string))
		logging_.log_level = TryToConvertToInt(tmp_string, tmp_int) ? tmp_int : logging_.log_level;

	if (TryToGetStringData("//root/logging/flush", tmp_string))
		logging_.flush = TryToConvertToInt(tmp_string, tmp_int) ? tmp_int : logging_.flush;

}

void CXMLParser::GetTimeConfigurationFromFile()
{
	std::string tmp_string;
	int tmp_int = 0;

	if (TryToGetStringData("//root/time/Period_time", tmp_string))
		time_.period_time = TryToConvertToInt(tmp_string, tmp_int) ? tmp_int : time_.period_time;

}

void CXMLParser::GetThreadPoolConfigurationFromFile()
{
	std::string tmp_string;
	int tmp_int = 0;

	if (TryToGetStringData("//root/threadpool/maxworkingthreads", tmp_string))
		thread_pool_.max_working_threads = TryToConvertToInt(tmp_string, tmp_int) ? tmp_int : thread_pool_.max_working_threads;

}

void CXMLParser::GetHDDInfoConfigurationFromFile()
{

	std::string tmp_string;
	int tmp_int = 0;
	bool tmp_bool = false;

	if (TryToGetStringData("//root/HDDinfo/filename", tmp_string))
		hdd_info_.file_name = tmp_string != "" ? tmp_string : hdd_info_.file_name;

	if (TryToGetStringData("//root/HDDinfo/checkhdd", tmp_string))
		hdd_info_.check_hdd = TryToConvertToBool(tmp_string, tmp_bool) ? tmp_bool : hdd_info_.check_hdd;

	if (TryToGetStringData("//root/HDDinfo/counttype", tmp_string))
		hdd_info_.count_type = TryToConvertToInt(tmp_string, tmp_int) ? tmp_int : hdd_info_.count_type;

}

void CXMLParser::GetProcessInfoConfigurationFromFile()
{

	std::string tmp_string;
	int tmp_int = 0;
	bool tmp_bool = false;

	if (TryToGetStringData("//root/processesinfo/filename", tmp_string))
		processes_info_.file_name = tmp_string != "" ? tmp_string : processes_info_.file_name;

	if (TryToGetStringData("//root/processesinfo/checkprocesses", tmp_string))
		processes_info_.check_processes = TryToConvertToBool(tmp_string, tmp_bool) ? tmp_bool : processes_info_.check_processes;

	if (TryToGetStringData("//root/processesinfo/counttype", tmp_string))
		processes_info_.count_type = TryToConvertToInt(tmp_string, tmp_int) ? tmp_int : processes_info_.count_type;

}

bool CXMLParser::TryToGetStringData(const std::string& data_path, std::string& return_data)
{
	pugi::xpath_node point;
	SearchNode(data_path, point);
	if (nullptr != point)
	{
		return_data = point.node().child_value();
		FormConfigurationString(return_data);
		return true;
	}
	return false;
}

void CXMLParser::SearchNode(const std::string& data_path, pugi::xpath_node& node) const
{
	node = p_file_->select_node(data_path.c_str());
	if (nullptr == node)
	{
		// report to logger
	}
}

void CXMLParser::FormConfigurationString(std::string& return_data)
{
	return_data = return_data.substr((return_data.find_first_of("\"") + 1),
		(return_data.find_last_of("\"") - 2));
}

bool CXMLParser::TryToConvertToBool(const std::string& data_to_convert, bool& return_data)
{
	const std::string on = "enable";
	const std::string off = "disable";
	if (on == data_to_convert)
	{
		return_data = true;
		return true;
	}
	else if (off == data_to_convert)
	{
		return_data = false;
		return true;
	}

	// todo: use logger
	std::cerr << "failed to convert data to bool" << std::endl;
	return false;
}

bool CXMLParser::TryToConvertToInt(const std::string& data_to_convert, int& return_data)
{
	try
	{
		size_t tmp;
		return_data = std::stoi(data_to_convert, &tmp);
		if (data_to_convert.size() != tmp)
			throw std::invalid_argument("Failed to convert data to integer");

		return true;
	}
	catch (const std::exception& e)
	{
		// todo: use logger
	}

	return false;
}

