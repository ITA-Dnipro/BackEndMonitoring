#include "stdafx.h"

#include "CClient.h"
#include "CClientView.h"
#include "ERequestType.h"

int main()
{
	int port = 1111;
	//std::string ip_address = "10.0.2.2";
	std::string ip_address = "127.0.0.1";

	CClientView view(std::cout, std::cin);
	CClient client(port, ip_address);
	bool result = true;
	ERequestType request;

	if (client.Connect())
	{
		view.PrintClientConnected();
	}
	else
	{
		view.PrintErrorConnection();
		system("pause");
		return -1;
	}

	do
	{
		view.PrintMenu();
		request = view.GetRequest();
		switch (request)
		{
		case ERequestType::ERR:
			view.PrintError();
			break;
		case ERequestType::ALL_DATA_CYCLE:
			for (unsigned i = 1u; i < 100; ++i)
			{
				std::cout << "\n_________" << i << "_________\n";
				result = client.MakeRequest(ERequestType::ALL_DATA);
			}
			break;
		default:
			result = client.MakeRequest(request);
			break;
		}
	} while (result && request != ERequestType::EXIT);
	view.PrintGoodbye();
	system("pause");
	return 0;
}
