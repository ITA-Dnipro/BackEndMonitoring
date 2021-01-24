#pragma once
#include "stdafx.h"
#include <typeinfo>

#include "Utils/Utils.h"

// Takes fifteenth argument from parameter pack
#define TAKE_15(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, N, ...) \
	N \
	
// Size of template parameter pack that less than fifteen
#define COUNT(...) \
	TAKE_15(__VA_ARGS__, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0) \

// Returns var itself
#define IDENTITY(var) var

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
#define FOR_EACH(F, ...) IDENTITY(APPLY(DISPATCH, COUNT(__VA_ARGS__)))(F, __VA_ARGS__) \

// Makes std::pair<std::const char*, Type> that contains
// var's name and var's value
#define MAKE_PAIR(x) \
	std::make_pair(std::string(GET_TYPE(x)) + " " + GET_NAME(x), x) \

// Prints all info-configs of logger
#define CLOG_INFO(logger) \
	(logger).PrintLogInfo() \

// Creates and prints CLogMessage of some CLogLevel via CLogger
#define CLOG_WRITE(logger, messageString, logLevel) \
    (logger).PrintLogMessage(CLogMessage(messageString, logLevel, __LINE__, \
                             LogUtils::GetFileNameByPath(__FILE__), __FUNCTION__, \
                             LogUtils::GetCurrentTimeString(), LogUtils::GetThisThreadIdString())) \

// Creates and prints CLogMessage with variable parameters of some CLogLevel via CLogger
#define CLOG_WRITE_WITH_PARAMS(logger, messageString, logLevel, ...) \
    (logger).PrintLogMessage(CLogMessage(messageString, logLevel, __LINE__, \
                             LogUtils::GetFileNameByPath(__FILE__), __FUNCTION__, \
                             LogUtils::GetCurrentTimeString(), LogUtils::GetThisThreadIdString(), \
							std::make_tuple(FOR_EACH(MAKE_PAIR, __VA_ARGS__)))) \

// Creates and prints CLogMessage that formed from exception of some CLogLevel via CLogger
#define CLOG_WRITE_EXCEPTION(logger, exception, logLevel) \
	CLOG_WRITE(logger, std::string("EXCEPTION!!!!") + " " + (exception).what(), logLevel) \

// Creates and prints CLogMessage that formed from variable creation of some CLogLevel via CLogger
#define CLOG_WRITE_VAR_CREATION(logger, var, logLevel) \
	CLOG_WRITE(logger, std::string("Created") + " " + GET_TYPE(var) + " " + GET_NAME(var) + ".", logLevel) \

// Creates and prints CLogMessage of PROD_LEVEL-level via CLogger
#define CLOG_PROD(logger, messageString) \
	CLOG_WRITE(logger, messageString, ELogLevel::PROD_LEVEL) \

// Creates and prints CLogMessage of PROD_LEVEL-level via CLogger with variable parameters 
#define CLOG_PROD_WITH_PARAMS(logger, messageString, ...) \
	CLOG_WRITE_WITH_PARAMS(logger, messageString, ELogLevel::PROD_LEVEL, __VA_ARGS__) \

// Creates and prints CLogMessage that formed from exception of PROD_LEVEL-level via CLogger
#define CLOG_PROD_EXCEPTION(logger, exception) \
	CLOG_WRITE_EXCEPTION(logger, exception, ELogLevel::PROD_LEVEL) \

// Creates and prints CLogMessage that formed from variable creation of PROD_LEVEL-level via CLogger
#define CLOG_PROD_VAR_CREATION(logger, var) \
	CLOG_WRITE_VAR_CREATION(logger, var, ELogLevel::PROD_LEVEL) \

// Creates and prints WARNING!! CLogMessage via CLogger
#define CLOG_WARNING(logger, messageString) \
	CLOG_PROD(logger, std::string("WARNING!!") + " " + (messageString)) \

// Creates and prints WARNING!! CLogMessage via CLogger with variable parameters
#define CLOG_WARNING_WITH_PARAMS(logger, messageString, ...) \
	CLOG_PROD_WITH_PARAMS(logger, std::string("WARNING!!") + " " + (messageString), __VA_ARGS__) \

// Creates and prints ERROR!!! CLogMessage via CLogger
#define CLOG_ERROR(logger, messageString) \
	CLOG_PROD(logger, std::string("ERROR!!!") + " " + (messageString)) \

// Creates and prints ERROR!!! CLogMessage via CLogger with variable parameters
#define CLOG_ERROR_WITH_PARAMS(logger, messageString, ...) \
	CLOG_PROD_WITH_PARAMS(logger, std::string("ERROR!!!") + " " + (messageString), __VA_ARGS__) \

// Creates and prints CLogMessage of DEBUG_LEVEL-level via CLogger
#define CLOG_DEBUG(logger, messageString) \
	CLOG_WRITE(logger, messageString, ELogLevel::DEBUG_LEVEL) \

// Creates and prints CLogMessage of DEBUG_LEVEL-level via CLogger with variable parameters
#define CLOG_DEBUG_WITH_PARAMS(logger, messageString, ...) \
	CLOG_WRITE_WITH_PARAMS(logger, messageString, ELogLevel::DEBUG_LEVEL, __VA_ARGS__) \

// Creates and prints CLogMessage that formed from exception of DEBUG_LEVEL-level via CLogger
#define CLOG_DEBUG_EXCEPTION(logger, exception) \
	CLOG_WRITE_EXCEPTION(logger, exception, ELogLevel::DEBUG_LEVEL) \

// Creates and prints CLogMessage that formed from variable creation of DEBUG_LEVEL-level via CLogger
#define CLOG_DEBUG_VAR_CREATION(logger, var) \
	CLOG_WRITE_VAR_CREATION(logger, var, ELogLevel::DEBUG_LEVEL) \

// Creates and prints CLogMessage of TRACE_LEVEL-level via CLogger
#define CLOG_TRACE(logger, messageString) \
	CLOG_WRITE(logger, messageString, ELogLevel::TRACE_LEVEL) \

// Creates and prints CLogMessage of TRACE_LEVEL-level via CLogger with variable parameters
#define CLOG_TRACE_WITH_PARAMS(logger, messageString, ...) \
	CLOG_WRITE_WITH_PARAMS(logger, messageString, ELogLevel::TRACE_LEVEL, __VA_ARGS__) \

// Creates and prints CLogMessage that formed from exception of TRACE_LEVEL-level via CLogger
#define CLOG_TRACE_EXCEPTION(logger, exception) \
	CLOG_WRITE_EXCEPTION(logger, exception, ELogLevel::TRACE_LEVEL) \

// Creates and prints CLogMessage that formed from variable creation of TRACE_LEVEL-level via CLogger
#define CLOG_TRACE_VAR_CREATION(logger, var) \
	CLOG_WRITE_VAR_CREATION(logger, var, ELogLevel::TRACE_LEVEL) \

#define CLOG_WRITE_START_FUNCTION(logger, logLevel) \
	CLOG_WRITE(logger, std::string(__FUNCTION__) + " " + "started", logLevel) \
	try { \

#define CLOG_WRITE_START_FUNCTION_WITH_PARAMS(logger, logLevel, ...) \
	CLOG_WRITE_WITH_PARAMS(logger, std::string(__FUNCTION__) + " " + "started", logLevel, __VA_ARGS__) \
	try { \

#define CLOG_WRITE_END_FUNCTION(logger, logLevel) \
	CLOG_WRITE(logger, std::string(__FUNCTION__) + " " + "ended", logLevel) \
	} catch (const std::exception& exception) { \
	CLOG_WRITE_EXCEPTION(logger, exception, logLevel) } \

#define CLOG_WRITE_END_FUNCTION_WITH_PARAMS(logger, logLevel, ...) \
	CLOG_WRITE(logger, std::string(__FUNCTION__) + " " + "ended", logLevel, __VA_ARGS__) \
	} catch (const std::exception& exception) { \
	CLOG_WRITE_EXCEPTION(logger, exception, logLevel) } \

#define CLOG_PROD_START_FUNCTION(logger) \
	CLOG_WRITE_START_FUNCTION(logger, ELogLevel::PROD_LEVEL) \

#define CLOG_PROD_START_FUNCTION_WITH_PARAMS(logger, ...) \
	CLOG_PROD_START_FUNCTION_WITH_PARAMS(logger, ELogLevel::PROD_LEVEL, __VA_ARGS__) \

#define CLOG_PROD_END_FUNCTION(logger) \
	CLOG_WRITE_END_FUNCTION(logger, ELogLevel::PROD_LEVEL) \

#define CLOG_PROD_END_FUNCTION_WITH_PARAMS(logger, ...) \
	CLOG_PROD_END_FUNCTION_WITH_PARAMS(logger, ELogLevel::PROD_LEVEL, __VA_ARGS__)

#define CLOG_DEBUG_START_FUNCTION(logger) \
	CLOG_WRITE_START_FUNCTION(logger, ELogLevel::DEBUG_LEVEL) \

#define CLOG_DEBUG_START_FUNCTION_WITH_PARAMS(logger, ...) \
	CLOG_PROD_START_FUNCTION_WITH_PARAMS(logger, ELogLevel::DEBUG_LEVEL, __VA_ARGS__) \

#define CLOG_DEBUG_END_FUNCTION(logger) \
	CLOG_WRITE_END_FUNCTION(logger, ELogLevel::DEBUG_LEVEL) \

#define CLOG_DEBUG_END_FUNCTION_WITH_PARAMS(logger, ...) \
	CLOG_PROD_END_FUNCTION_WITH_PARAMS(logger, ELogLevel::DEBUG_LEVEL, __VA_ARGS__)

#define CLOG_TRACE_START_FUNCTION(logger) \
	CLOG_WRITE_START_FUNCTION(logger, ELogLevel::TRACE_LEVEL) \

#define CLOG_TRACE_START_FUNCTION_WITH_PARAMS(logger, ...) \
	CLOG_PROD_START_FUNCTION_WITH_PARAMS(logger, ELogLevel::TRACE_LEVEL, __VA_ARGS__) \

#define CLOG_TRACE_END_FUNCTION(logger) \
	CLOG_WRITE_END_FUNCTION(logger, ELogLevel::TRACE_LEVEL) \

#define CLOG_TRACE_END_FUNCTION_WITH_PARAMS(logger, ...) \
	CLOG_PROD_END_FUNCTION_WITH_PARAMS(logger, ELogLevel::TRACE_LEVEL, __VA_ARGS__)
