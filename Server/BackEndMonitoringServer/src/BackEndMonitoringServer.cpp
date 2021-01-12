#include "stdafx.h"

#include <iostream>
#include "CAcceptorWrapper.h"
#include "CThreadPool.h"

int main( )
{
	CEvent event;
	size_t num_threads = 3;
	//std::cout << "Hello World!\n";
	CAcceptorWrapper acceptor(num_threads, event);

	acceptor.Start();
	system("pause");
	return 0;
}

