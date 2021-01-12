#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <map>

#ifndef _linux_
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#endif
