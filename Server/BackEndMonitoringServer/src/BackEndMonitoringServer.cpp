#include "stdafx.h"

#include <iostream>

#include "XMLParser.h"

int main(int argc, char** argv)
{
	XMLParser xml_parser("D:\\xgconsole.xml");
	int a; 
	if (xml_parser.TryToGetIntegerConfiguration("//root/time/Period_time", a))
	{
		std::cout << a << std::endl;
	}

	std::string data; 
	if (xml_parser.TryToGetStringConfiguration("//root/Server/serverdisplayname", data))
	{
		std::cout << data << std::endl;
	}

	if (xml_parser.IsConfigurationEnabled("//root/HDDinfo/checkhdd"))
	{
		std::cout << "enabled" << std::endl;
	}
	else
	{
		std::cout << "disabled" << std::endl;
	}


}

