#pragma once

struct SServer
{
	std::string server_name = "ServTest";
	std::string server_displayname = "ServTestserver";
	int listener_port = 25000;
	std::string ip_address = "127.0.0.1";
};

struct SComunicationSettings
{
	int blocking = 0;
	int socket_timeout = 5;
};

struct SLogging
{
	std::string file_name = "serverlog.txt";
	int log_level = 2;
	int flush = 0;
};

struct STime
{
	int period_time = 30;
};

struct SThreadPool
{
	int max_working_threads = 10;
};

struct SHDDInfo
{
	std::string file_name = "hddinfo.txt";
	bool check_hdd = true;
	int count_type = 0;
};

struct SProcessesInfo
{
	std::string file_name = "processesinfo.txt";	
	bool check_processes = true;
	int count_type = 0;
};