#pragma once
#include "stdafx.h"

#include "Utils/Utils.h"
#include "GlobalLogger.h"

// Takes fifteenth argument from parameter pack
#define TAKE_15(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, N, ...) \
	N \

// Size of template parameter pack that less than fifteen
#define COUNT(...) \
	TAKE_15(__VA_ARGS__, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0) \

// Returns var itself
#define IDENTITY(var) var

#define RIGHT_COUNT(...) IDENTITY(COUNT(__VA_ARGS__))

// Unites macro command and variable arguments args
#define APPLY(macro, ...) \
	IDENTITY(macro(__VA_ARGS__)) \

#define F_0(F)
#define F_1(F, a) F(a)
#define F_2(F, a, b) F(a), F(b)
#define F_3(F, a, b, c) F(a), F(b), F(c)
#define F_4(F, a, b, c, d) F(a), F(b), F(c), F(d)
#define F_5(F, a, b, c, d, e) F(a), F(b), F(c), F(d), F(e)
#define F_6(F, a, b, c, d, e, f) F(a), F(b), F(c), F(d), F(e), F(f)
#define F_7(F, a, b, c, d, e, f, g) F(a), F(b), F(c), F(d), F(e), F(f), F(g)
#define F_8(F, a, b, c, d, e, f, g, h) F(a), F(b), F(c), F(d), F(e), F(f), F(g), F(h)
#define F_9(F, a, b, c, d, e, f, g, h, i) F(a), F(b), F(c), F(d), F(e), F(f), F(g), F(h), F(i)
#define F_10(F, a, b, c, d, e, f, g, h, i, j) F(a), F(b), F(c), F(d), F(e), F(f), F(g), F(h), F(i), F(j)
#define F_11(F, a, b, c, d, e, f, g, h, i, j, k) F(a), F(b), F(c), F(d), F(e), F(f), F(g), F(h), F(i), F(j), F(k)
#define F_12(F, a, b, c, d, e, f, g, h, i, j, k, l) F(a), F(b), F(c), F(d), F(e), F(f), F(g), F(h), F(i), F(j), F(k), F(l)
#define F_13(F, a, b, c, d, e, f, g, h, i, j, k, l, m) F(a), F(b), F(c), F(d), F(e), F(f), F(g), F(h), F(i), F(j), F(k), F(l), F(m)
#define F_14(F, a, b, c, d, e, f, g, h, i, j, k, l, m, n) F(a), F(b), F(c), F(d), F(e), F(f), F(g), F(h), F(i), F(j), F(k), F(l), F(m), F(n)
#define F_15(F, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o) F(a), F(b), F(c), F(d), F(e), F(f), F(g), F(h), F(i), F(j), F(k), F(l), F(m), F(n), F(o)

// Returns var name
#define GET_NAME(x) #x \

// Returns var type
#define GET_TYPE(x) \
	typeid(x).name() \

// Concatenation of F_ and some var
#define DISPATCH(N) \
	F_ ## N \

// Macro foreach function
#define FOR_EACH(F, ...) IDENTITY(APPLY(DISPATCH, RIGHT_COUNT(__VA_ARGS__)))(F, __VA_ARGS__) \

// Makes std::pair<std::const char*, Type> that contains
// var's name and var's value
#define MAKE_PAIR(x) \
	std::make_pair(std::string(GET_TYPE(x)) + " " + GET_NAME(x), x) \

// Prints all info-configs of logger
#define CLOG_INFO() \
	CLog::GetLogger()->PrintLogInfo() \

// Creates and prints CLogMessage of some CLogLevel via CLogger
#define CLOG_WRITE(messageString, logLevel) \
    CLog::GetLogger()->PrintLogMessage(CLogMessage(messageString, logLevel, __LINE__, \
                            LogUtils::GetFileNameByPath(__FILE__), __FUNCTION__, \
                            LogUtils::GetTime(), LogUtils::GetThisThreadIdString())) \

// Creates and prints CLogMessage with variable parameters of some CLogLevel via CLogger
#define CLOG_WRITE_WITH_PARAMS(messageString, logLevel, ...) \
    CLog::GetLogger()->PrintLogMessage(CLogMessage(messageString, logLevel, __LINE__, \
                            LogUtils::GetFileNameByPath(__FILE__), __FUNCTION__, \
                            LogUtils::GetTime(), LogUtils::GetThisThreadIdString(), \
							std::make_tuple(FOR_EACH(MAKE_PAIR, __VA_ARGS__)))) \

// Creates and prints CLogMessage that formed from exception of some CLogLevel via CLogger
#define CLOG_WRITE_EXCEPTION(exception, logLevel) \
	CLOG_WRITE(std::string("EXCEPTION!!!!") + " " + (exception).what(), logLevel) \

// Creates and prints CLogMessage that formed from variable creation of some CLogLevel via CLogger
#define CLOG_WRITE_VAR_CREATION(var, logLevel) \
	CLOG_WRITE(std::string("Created var") + " " + GET_TYPE(var) + " " + GET_NAME(var) + ".", logLevel) \

// Creates and prints CLogMessage of PROD_LEVEL-level via CLogger
#define CLOG_PROD(messageString) \
	CLOG_WRITE(messageString, ELogLevel::PROD_LEVEL) \

// Creates and prints CLogMessage of PROD_LEVEL-level via CLogger with variable parameters 
#define CLOG_PROD_WITH_PARAMS(messageString, ...) \
	CLOG_WRITE_WITH_PARAMS(messageString, ELogLevel::PROD_LEVEL, __VA_ARGS__) \

// Creates and prints CLogMessage that formed from exception of PROD_LEVEL-level via CLogger
#define CLOG_PROD_EXCEPTION(exception) \
	CLOG_WRITE_EXCEPTION(exception, ELogLevel::PROD_LEVEL) \

// Creates and prints CLogMessage that formed from variable creation of PROD_LEVEL-level via CLogger
#define CLOG_PROD_VAR_CREATION(var) \
	CLOG_WRITE_VAR_CREATION(var, ELogLevel::PROD_LEVEL) \

// Creates and prints WARNING!! CLogMessage via CLogger
#define CLOG_WARNING(messageString) \
	CLOG_PROD(std::string("WARNING!!") + " " + (messageString)) \

// Creates and prints WARNING!! CLogMessage via CLogger with variable parameters
#define CLOG_WARNING_WITH_PARAMS(messageString, ...) \
	CLOG_PROD_WITH_PARAMS(std::string("WARNING!!") + " " + (messageString), __VA_ARGS__) \

// Creates and prints ERROR!!! CLogMessage via CLogger
#define CLOG_ERROR(messageString) \
	CLOG_PROD(std::string("ERROR!!!") + " " + (messageString)) \

// Creates and prints ERROR!!! CLogMessage via CLogger with variable parameters
#define CLOG_ERROR_WITH_PARAMS(messageString, ...) \
	CLOG_PROD_WITH_PARAMS(std::string("ERROR!!!") + " " + (messageString), __VA_ARGS__) \

// Creates and prints CLogMessage of DEBUG_LEVEL-level via CLogger
#define CLOG_DEBUG(messageString) \
	CLOG_WRITE(messageString, ELogLevel::DEBUG_LEVEL) \

// Creates and prints CLogMessage of DEBUG_LEVEL-level via CLogger with variable parameters
#define CLOG_DEBUG_WITH_PARAMS(messageString, ...) \
	CLOG_WRITE_WITH_PARAMS(messageString, ELogLevel::DEBUG_LEVEL, __VA_ARGS__) \

// Creates and prints CLogMessage that formed from exception of DEBUG_LEVEL-level via CLogger
#define CLOG_DEBUG_EXCEPTION(exception) \
	CLOG_WRITE_EXCEPTION(exception, ELogLevel::DEBUG_LEVEL) \

// Creates and prints CLogMessage that formed from variable creation of DEBUG_LEVEL-level via CLogger
#define CLOG_DEBUG_VAR_CREATION(var) \
	CLOG_WRITE_VAR_CREATION(var, ELogLevel::DEBUG_LEVEL) \

// Creates and prints CLogMessage of TRACE_LEVEL-level via CLogger
#define CLOG_TRACE(messageString) \
	CLOG_WRITE(messageString, ELogLevel::TRACE_LEVEL) \

// Creates and prints CLogMessage of TRACE_LEVEL-level via CLogger with variable parameters
#define CLOG_TRACE_WITH_PARAMS(messageString, ...) \
	CLOG_WRITE_WITH_PARAMS(messageString, ELogLevel::TRACE_LEVEL, __VA_ARGS__) \

// Creates and prints CLogMessage that formed from exception of TRACE_LEVEL-level via CLogger
#define CLOG_TRACE_EXCEPTION(exception) \
	CLOG_WRITE_EXCEPTION(exception, ELogLevel::TRACE_LEVEL) \

// Creates and prints CLogMessage that formed from variable creation of TRACE_LEVEL-level via CLogger
#define CLOG_TRACE_VAR_CREATION(var) \
	CLOG_WRITE_VAR_CREATION(var, ELogLevel::TRACE_LEVEL) \

#define CLOG_WRITE_START_FUNCTION(logLevel) \
	CLOG_WRITE(std::string(__FUNCTION__) + " " + "function started", logLevel); \
	try { \

#define CLOG_WRITE_START_FUNCTION_WITH_PARAMS(logLevel, ...) \
	CLOG_WRITE_WITH_PARAMS(std::string(__FUNCTION__) + " " + "function started", logLevel, __VA_ARGS__); \
	try { \

#define CLOG_WRITE_END_FUNCTION(logLevel) \
	CLOG_WRITE(std::string(__FUNCTION__) + " " + "function ended", logLevel); \
	} catch (const std::exception& exception) { \
	CLOG_WRITE_EXCEPTION(exception, logLevel); } \

#define CLOG_WRITE_END_FUNCTION_RETURN(logLevel, value) \
	CLOG_WRITE_WITH_PARAMS(std::string(__FUNCTION__) + " " + "function ended", logLevel, value); \
	} catch (const std::exception& exception) { \
	CLOG_WRITE_EXCEPTION(exception, logLevel); \
	return value; } \

#define CLOG_PROD_START_FUNCTION() \
	CLOG_WRITE_START_FUNCTION(ELogLevel::PROD_LEVEL) \

#define CLOG_PROD_START_FUNCTION_WITH_PARAMS(...) \
	CLOG_WRITE_START_FUNCTION_WITH_PARAMS(ELogLevel::PROD_LEVEL, __VA_ARGS__) \

#define CLOG_PROD_END_FUNCTION() \
	CLOG_WRITE_END_FUNCTION(ELogLevel::PROD_LEVEL) \

#define CLOG_PROD_END_FUNCTION_WITH_RETURN(value) \
	CLOG_WRITE_END_FUNCTION_RETURN(ELogLevel::PROD_LEVEL, value)

#define CLOG_DEBUG_START_FUNCTION() \
	CLOG_WRITE_START_FUNCTION(ELogLevel::DEBUG_LEVEL) \

#define CLOG_DEBUG_START_FUNCTION_WITH_PARAMS(...) \
	CLOG_WRITE_START_FUNCTION_WITH_PARAMS(ELogLevel::DEBUG_LEVEL, __VA_ARGS__) \

#define CLOG_DEBUG_END_FUNCTION() \
	CLOG_WRITE_END_FUNCTION(ELogLevel::DEBUG_LEVEL) \

#define CLOG_DEBUG_END_FUNCTION_WITH_RETURN(value) \
	CLOG_WRITE_END_FUNCTION_RETURN(ELogLevel::DEBUG_LEVEL, value) \

#define CLOG_TRACE_START_FUNCTION() \
	CLOG_WRITE_START_FUNCTION(ELogLevel::TRACE_LEVEL) \

#define CLOG_TRACE_START_FUNCTION_WITH_PARAMS(...) \
	CLOG_WRITE_START_FUNCTION_WITH_PARAMS(ELogLevel::TRACE_LEVEL, __VA_ARGS__) \

#define CLOG_TRACE_END_FUNCTION() \
	CLOG_WRITE_END_FUNCTION(ELogLevel::TRACE_LEVEL) \

#define CLOG_TRACE_END_FUNCTION_WITH_RETURN(value) \
	CLOG_WRITE_END_FUNCTION_RETURN(ELogLevel::TRACE_LEVEL, value)
