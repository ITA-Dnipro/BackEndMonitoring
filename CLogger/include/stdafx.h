#pragma once

#define DEMODLL_EXPORTS

//#define CLOGGER_EXTERN_C extern "C"

#ifdef DEMODLL_EXPORTS
	#define CLOGGER_API __declspec(dllexport)
#else
	#define CLOGGER_API __declspec(dllimport)
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
