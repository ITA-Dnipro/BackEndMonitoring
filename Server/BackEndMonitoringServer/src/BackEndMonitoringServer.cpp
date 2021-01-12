#include "stdafx.h"

#include <iostream>

#include "XMLParser.h"

int main(int argc, char** argv)
{
	std::cout << argv[0] << std::endl;
	XMLParser xml_parser("D:\\xgconsole.xml");
	std::cout << xml_parser.getStringConfiguration("//root/Server/serverdisplayname") << std::endl;
	std::cout << xml_parser.getIntegerConfiguration("//root/time/Period_time") << std::endl;
	std::cout << xml_parser.getIntegerConfiguration("//root/HDDinfo/counttype") << std::endl;
	if (xml_parser.isConfigurationEnabled("//root/HDDinfo/checkhdd"))
	{
		std::cout << "enabled" << std::endl;
	}
	else
	{
		std::cout << "disabled" << std::endl;
	}


}

