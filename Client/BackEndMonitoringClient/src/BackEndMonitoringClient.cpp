#include "stdafx.h"

#include <iostream>
#include "CConnectorWrapper.h"

int main()
{
    //std::cout << "Hello World!\n";

	CConnectorWrapper connector;

	connector.MakeRequest("hello world!");

	system("pause");
}
