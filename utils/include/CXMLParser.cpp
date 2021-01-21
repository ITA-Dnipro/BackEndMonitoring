#include "stdafx.h"
#include "CXMLParser.h"


bool CXMLParser::Initialize(const std::string& path_to_configuration_file)
{
	p_docfile_ = std::move(std::make_unique<pugi::xml_document>());
	return p_docfile_->load_file(path_to_configuration_file.c_str());
}

SServer& CXMLParser::TryToGetServerConfigurationFromFile()
{
	if (nullptr == p_docfile_)
	{
		// todo: write to logger
		return server_;
	}

	std::string tmp_string;
	int tmp_int;

	tmp_string = p_docfile_->child("root").child("Server").child("servername").child_value();
	FormConfigurationString(tmp_string);
	server_.server_name = tmp_string != "" ? tmp_string : server_.server_name;

	tmp_string = p_docfile_->child("root").child("Server").child("serverdisplayname").child_value();
	FormConfigurationString(tmp_string);
	server_.server_displayname = tmp_string != "" ? tmp_string : server_.server_displayname;

	tmp_string = p_docfile_->child("root").child("Server").child("listenerport").child_value();
	FormConfigurationString(tmp_string);
	server_.listener_port = TryToConvertToInt(tmp_string, tmp_int) ? tmp_int : server_.listener_port;

	tmp_string = p_docfile_->child("root").child("Server").child("ipaddress").child_value();
	FormConfigurationString(tmp_string);
	server_.ip_address = tmp_string != "" ? tmp_string : server_.ip_address;

	return server_;

}

SComunicationSettings& CXMLParser::TryToGetComunicationConfigurationFromFile()
{
	if (nullptr == p_docfile_)
	{
		// todo: write to logger
		return comunication_settings_;
	}

	std::string tmp_string;
	int tmp_int;

	tmp_string = p_docfile_->child("root").child("communicationsettings").child("blocking").child_value();
	FormConfigurationString(tmp_string);
	comunication_settings_.blocking = TryToConvertToInt(tmp_string, tmp_int) ? tmp_int : comunication_settings_.blocking;

	tmp_string = p_docfile_->child("root").child("communicationsettings").child("socket_timeout").child_value();
	FormConfigurationString(tmp_string);
	comunication_settings_.socket_timeout = TryToConvertToInt(tmp_string, tmp_int) ? tmp_int : comunication_settings_.socket_timeout;
	
	return comunication_settings_;

}

SLogging& CXMLParser::TryToGetLoggingConfigurationFromFile()
{
	if (nullptr == p_docfile_)
	{
		// todo: write to logger
		return logging_;
	}

	std::string tmp_string;
	int tmp_int;

	tmp_string = p_docfile_->child("root").child("logging").child("filename").child_value();
	FormConfigurationString(tmp_string);
	logging_.file_name = tmp_string != "" ? tmp_string : logging_.file_name;

	tmp_string = p_docfile_->child("root").child("logging").child("LogLevel").child_value();
	FormConfigurationString(tmp_string);
	logging_.log_level = TryToConvertToInt(tmp_string, tmp_int) ? tmp_int : logging_.log_level;

	tmp_string = p_docfile_->child("root").child("logging").child("LogLevel").child_value();
	FormConfigurationString(tmp_string);
	logging_.flush = TryToConvertToInt(tmp_string, tmp_int) ? tmp_int : logging_.flush;

	return logging_;

}

STime& CXMLParser::TryToGetTimeConfigurationFromFile()
{
	if (nullptr == p_docfile_)
	{
		// todo: write to logger
		return time_;
	}

	std::string tmp_string;
	int tmp_int;

	tmp_string = p_docfile_->child("root").child("time").child("Period_time").child_value();
	FormConfigurationString(tmp_string);
	time_.period_time = TryToConvertToInt(tmp_string, tmp_int) ? tmp_int : time_.period_time;

	return time_;

}

SThreadPool& CXMLParser::TryToGetThreadPoolConfigurationFromFile()
{
	if (nullptr == p_docfile_)
	{
		// todo: write to logger
		return thread_pool_;
	}

	std::string tmp_string;
	int tmp_int;

	tmp_string = p_docfile_->child("root").child("threadpool").child("maxworkingthreads").child_value();
	FormConfigurationString(tmp_string);
	thread_pool_.max_working_threads = TryToConvertToInt(tmp_string, tmp_int) ? tmp_int : thread_pool_.max_working_threads;
	
	return thread_pool_;

}

SHDDInfo& CXMLParser::TryToGetHDDInfoConfigurationFromFile()
{
	if (nullptr == p_docfile_)
	{
		// todo: write to logger
		return hdd_info_;
	}

	std::string tmp_string;
	int tmp_int;
	bool tmp_bool;

	tmp_string = p_docfile_->child("root").child("HDDinfo").child("filename").child_value();
	FormConfigurationString(tmp_string);
	hdd_info_.file_name = tmp_string != "" ? tmp_string : hdd_info_.file_name;

	tmp_string = p_docfile_->child("root").child("HDDinfo").child("checkhdd").child_value();
	FormConfigurationString(tmp_string);
	hdd_info_.check_hdd = TryToConvertToBool(tmp_string, tmp_bool) ? tmp_bool : hdd_info_.check_hdd;

	tmp_string = p_docfile_->child("root").child("HDDinfo").child("counttype").child_value();
	FormConfigurationString(tmp_string);
	hdd_info_.count_type = TryToConvertToInt(tmp_string, tmp_int) ? tmp_int : hdd_info_.count_type;

	return hdd_info_;

}

SProcessesInfo& CXMLParser::TryToGetProcessInfoConfigurationFromFile()
{
	if (nullptr == p_docfile_)
	{
		// todo: write to logger
		return processes_info_;
	}

	std::string tmp_string;
	int tmp_int;
	bool tmp_bool;

	tmp_string = p_docfile_->child("root").child("processesinfo").child("filename").child_value();
	FormConfigurationString(tmp_string);
	processes_info_.file_name = tmp_string != "" ? tmp_string : processes_info_.file_name;

	tmp_string = p_docfile_->child("root").child("processesinfo").child("checkprocesses").child_value();
	FormConfigurationString(tmp_string);
	processes_info_.check_processes = TryToConvertToBool(tmp_string, tmp_bool) ? tmp_bool : processes_info_.check_processes;

	tmp_string = p_docfile_->child("root").child("processesinfo").child("counttype").child_value();
	FormConfigurationString(tmp_string);
	processes_info_.count_type = TryToConvertToInt(tmp_string, tmp_int) ? tmp_int : processes_info_.count_type;

	return processes_info_;

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
			return false;
			// todo: use logger
		return true;
	}
	catch (const std::exception& e)
	{
		// todo: use logger
	}

		return false;
}

