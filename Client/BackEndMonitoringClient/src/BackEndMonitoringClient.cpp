#include "stdafx.h"
#include "CClient.h"

int main()
{
	int port = 1111;
	//std::string ip_address = "10.0.2.2";
	std::string ip_address = "10.0.2.15";

	CClient client(port, ip_address);

	client.MakeRequest();
	system("pause");
}
