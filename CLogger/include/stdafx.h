#pragma once

#ifdef _WIN32
    #define CLOG_SYS_WINDOWS
    // defined to disable <Window.h> from defining
    // the min and max macros
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif

#elif defined(__linux__)
    #define CLOG_SYS_LINUX
#elif defined(__APPLE__)
    #define CLOG_SYS_MACOS
#endif


#ifdef CLOG_STATIC_BUILD
    #define CLOGGER_API
#else
    #ifdef CLOG_SYS_WINDOWS
        #define DEMODLL_EXPORTS
        #ifdef CLOG_NONCLIENT_BUILD
            #ifdef DEMODLL_EXPORTS
                #define CLOGGER_API __declspec(dllexport)
            #else
                #define CLOGGER_API __declspec(dllimport)
            #endif
        #endif

        #ifdef _MSC_VER
            #pragma warning(disable : 4251)
            #pragma warning(disable : 5105)
        #endif
    #elif defined(CLOG_SYS_LINUX) || defined(CLOG_SYS_MACOS)
        #if _GNUC_ >= 4
            #define CLOGGER_API __attribute__((__visibility__("default")))
        #else
            #define CLOGGER_API
        #endif
    #endif
#endif

#include <filesystem>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <ostream>
#include <sstream>
#include <string>
#include <thread>
#include <typeinfo>