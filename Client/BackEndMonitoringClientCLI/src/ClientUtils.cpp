#include "stdafx.h"
#include "ClientUtils.h"
#include "GlobalVariable.h"

namespace ClientUtils
{
	int ConvertToInt(const std::string port_str)
	{
		int number = 0;

		try
		{
			number = std::stol(port_str);
		}
		catch (std::invalid_argument)
		{
			number = -1;
		}
		catch (std::out_of_range)
		{
			number = -1;
		}

		return number;
	}

	bool IsValidPort(const int port)
	{
		if (port > 0 && port < GlobalVariable::c_max_port_value)
		{
			return true;
		}
		return false;
	}

	bool IsValidIpAddress(const std::string& ip_address)
	{
		if (ip_address.size() < c_min_ip_address_size
			|| ip_address.size() > c_max_ip_address_size)
		{
			return false;
		}
		
		int count_valid_octets = 0;
		int count_points = 0;
		const int max_num_points = 3;
		const int num_validated_octets = 4;
		const char point = '.';
		std::string octet;
		
		for(size_t i = 0ULL; i < ip_address.size(); ++i)
		{
			if(i != 0 && ip_address[i] == point && count_points < max_num_points)
			{
				++count_points;
				continue;
			}
			if(!isdigit(ip_address[i]))
			{
				return false;
			}

			octet += ip_address[i];
			if((i == ip_address.size() - 1ULL || ip_address[i + 1ULL] == point )
				&& IsValidOctet(octet))
			{
				++count_valid_octets;
				octet.clear();
			}
		}
		if (count_valid_octets == num_validated_octets)
		{
			return true;
		}

		return false;
	}

	bool IsValidOctet(const std::string& octet)
	{
		bool res = false;
		int converted_num = ConvertToInt(octet);
		if(converted_num >= c_min_valid_octet && converted_num <= c_max_valid_octet)
		{
			return true;
		}
		return false;
	}
}
