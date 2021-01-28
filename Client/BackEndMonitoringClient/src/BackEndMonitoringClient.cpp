#include "stdafx.h"
#include "CClient.h"

int main()
{
	int port = 1111;
	std::string ip_address = "127.0.0.1";

	CClient client(port, ip_address);

	client.MakeRequest();
	system("pause");
}
