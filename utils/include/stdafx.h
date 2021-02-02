#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #define BACK_END_MONITORING_SYS_WINDOWS
    // defined to disable <Window.h> from defining
    // the min and max macros
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif

#elif defined(__linux__)
    #define  BACK_END_MONITORING_SYS_LINUX
#elif defined(__APPLE__)
    #define BACK_END_MONITORING_SYS_MACOS
#endif


#ifdef CLOG_STATIC_BUILD
    #define CLOGGER_API
#else
    #ifdef BACK_END_MONITORING_SYS_WINDOWS
        #define DEMODLL_EXPORTS

        #ifdef DEMODLL_EXPORTS
            #define CLOGGER_API __declspec(dllexport)
        #else
            #define CLOGGER_API __declspec(dllimport)
        #endif

        #ifdef _MSC_VER
            #pragma warning(disable : 4251)
            #pragma warning(disable : 5105)
        #endif
    #elif defined(BACK_END_MONITORING_SYS) || defined(BACK_END_MONITORING_SYS_MACOS)
        #if _GNUC_ >= 4
            #define CLOGGER_API __attribute__((__visibility__("default")))
        #else
            #define CLOGGER_API
        #endif
    #endif
#endif

#ifdef BACK_END_MONITORING_SYS_WINDOWS
	#include <WinSock2.h>
	#include <ws2tcpip.h>
	#pragma comment(lib, "ws2_32.lib")
	#include <Windows.h>
	#include <psapi.h>
	#include <WtsApi32.h>
	#include <strsafe.h>
	#include <atlstr.h>
#elif defined(BACK_END_MONITORING_SYS_LINUX) || defined(BACK_END_MONITORING_SYS_MACOS)
#include <ctime>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <unistd.h>
	#include <cstdio>
	#include <cstdlib>
	#include <sys/socket.h>
	#include <netinet/ip.h>
	#include <netdb.h>
	#include <arpa/inet.h>
	#include <sys/ioctl.h>
	#include <csignal>
#endif

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
#include <cassert>
#include <memory>
#include <algorithm>
#include <optional>
#include <typeinfo>
#include <sstream>

#include "json.hpp"
