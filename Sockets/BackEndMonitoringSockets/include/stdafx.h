#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <optional>
#include <thread>
#include <filesystem>

#include "json.hpp"

#if defined(_WIN64) || defined(_WIN32)

#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include <Windows.h>
#include <psapi.h>
#elif __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#endif