#include "stdafx.h"

#include "CClient.h"

int main( )
{
	int port = 1111;
	//std::string ip_address = "10.0.2.2";
	std::string ip_address = "127.0.0.1";
	std::string file_name = "ServerMessages.txt";

	CClient client(port, ip_address, file_name);

	client.Execute( );

	system("pause");
	return 0;
}