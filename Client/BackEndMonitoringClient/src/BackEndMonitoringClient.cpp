#include "stdafx.h"

#include "CClient.h"

int main(const int argc, char* argv[])
{
	CClient client;

	if (client.Init(argc, argv))
	{
		client.Execute();
	}
	else
	{
		std::cout << "Wrong parameters for the network!" << std::endl;
	}

	return 0;
}