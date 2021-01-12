#pragma once

#define DEMODLL_EXPORTS

//#define CLOGGER_EXTERN_C extern "C"

#ifdef DEMODLL_EXPORTS
	#define CLOGGER_API __declspec(dllexport)
#else
	#define CLOGGER_API __declspec(dllimport)
#endif

#include <string>
#include <list>
#include <mutex>
#include <ostream>
#include <sstream>