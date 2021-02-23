#pragma once

enum class Arguments : size_t
{
	PORT_FLAG = 1,
	PORT,
	IP_FLAG,
	IP,
	COUNT
};
namespace ClientUtils
{
	
	int ConvertToInt(const std::string port_str);
	bool IsValidPort(const int port);
	bool IsValidIpAddress(const std::string& ip_address);
	bool IsValidOctet(const std::string& octet);
	
	constexpr size_t c_max_ip_address_size = 15ULL;
	constexpr size_t c_min_ip_address_size = 4ULL;
	constexpr int c_max_valid_octet = 255;
	constexpr int c_min_valid_octet = 0;

	static const std::string c_port_flag = "-port";
	static const std::string c_ip_address_flag = "-ip";
};
