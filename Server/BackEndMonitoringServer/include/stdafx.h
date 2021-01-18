#pragma once

#include <iostream>
#include <future>
#include <queue>
#include <condition_variable>
#include <functional>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>
#include <filesystem>
#include <cmath>
#include <unordered_map>
#include <list>
#include <vector>

#ifndef _linux_
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include <Windows.h>
#include <psapi.h>
#endif
