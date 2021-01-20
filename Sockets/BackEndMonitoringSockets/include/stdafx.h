#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <map>

#ifdef _WIN64

	#include <WinSock2.h>
	#include <ws2tcpip.h>
	#pragma comment(lib, "ws2_32.lib")
#elif _linux_
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <stdlib.h>
#endif