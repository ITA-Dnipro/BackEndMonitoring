#include "stdafx.h"

#include "CClient.h"
#include "CClientView.h"
#include "ERequestType.h"

int main()
{
	int port = 1111;
	//std::string ip_address = "10.0.2.2";
	std::string ip_address = "10.0.2.15";

	CClientView view(std::cout, std::cin);
	CClient client(port, ip_address);
	client.Connect();
	
	ERequestType request;
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
			for (unsigned i = 0u; i < 20; ++i)
			{
				std::cout << "\n_________" << i << "_________\n";
				view.PrintResult(client.MakeRequest(ERequestType::ALL_DATA));
				Sleep(500);
			}
			break;
		default:
			view.PrintResult(client.MakeRequest(request));
			break;
		}
	} while (request != ERequestType::EXIT);
	view.PrintGoodbye();
	system("pause");
}
