#pragma once
#include "stdafx.h"

#include <thread>

/// <summary>
///		Gets current thread's id in <c>std::string</c>
/// </summary>
/// <returns>
///		String, that contains thread_id
/// </returns>
/// <example>
///		std::string thisThread = ThisThreadGetIdString();
/// </example>
inline std::string ThisThreadGetIdString()
{
	std::stringstream ss;
	ss << std::this_thread::get_id();
	return ss.str();
}

#define TAKE_15(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, N, ...) N
#define COUNT(...) TAKE_15(__VA_ARGS__, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

//#define GET_VA_ARGS_SIZE(...) ((int)(sizeof((int[])(__VA_ARGS__ ))/sizeof(int)))

#define IDENTITY(var) var
#define APPLY(macro, ...) IDENTITY(macro(__VA_ARGS__))

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

#define GET_NAME(x) #x

#define DISPATCH(N) F_ ## N

#define FOR_EACH(F, ...) IDENTITY(APPLY(DISPATCH, COUNT(__VA_ARGS__)))(F, __VA_ARGS__)

#define MAKE_PAIR(x) std::make_pair(GET_NAME(x), x)

#define WRITE_INFO_LOG(logger) \
	(logger).PrintLogInfo() \

#define WRITE_LOG(logger, messageString, logLevel) \
    (logger).PrintLogMessage(CLogMessage(messageString, logLevel, __LINE__, \
                             std::filesystem::path(__FILE__).filename().string(), \
                             __FUNCTION__, __TIMESTAMP__, ThisThreadGetIdString())) \

#define WRITE_LOG_WITH_PARAMS(logger, messageString, logLevel, ...) \
    (logger).PrintLogMessage(CLogMessage(messageString, logLevel, __LINE__, \
                             std::filesystem::path(__FILE__).filename().string(), \
                             __FUNCTION__, __TIMESTAMP__, ThisThreadGetIdString(), \
							std::make_tuple(FOR_EACH(MAKE_PAIR, __VA_ARGS__)))) \

#define WRITE_LOG_EXCEPTION(logger, exception, logLevel) \
	    (logger).PrintLogMessage(CLogMessage(std::string("EXCEPTION!!!!") + " " + (exception).what(), \
							logLevel, __LINE__, std::filesystem::path(__FILE__).filename().string(), \
                            __FUNCTION__, __TIMESTAMP__, ThisThreadGetIdString())) \

#define WRITE_PROD(logger, messageString) \
	WRITE_LOG(logger, messageString, ELogLevel::PROD) \

#define WRITE_PROD_WITH_PARAMS(logger, messageString, ...) \
	WRITE_LOG_WITH_PARAMS(logger, messageString, ELogLevel::PROD, __VA_ARGS__) \

#define WRITE_PROD_EXCEPTION(logger, exception) \
	WRITE_LOG_EXCEPTION(logger, exception, ELogLevel::PROD) \

#define WRITE_WARNING(logger, messageString) \
	WRITE_PROD(logger, string("WARNING!!") + " " + (messageString)) \

#define WRITE_WARNING_WITH_PARAMS(logger, messageString, ...) \
	WRITE_PROD(logger, string("WARNING!!") + " " + (messageString), __VA_ARGS__) \

#define WRITE_ERROR(logger, messageString) \
	WRITE_PROD(logger, string("ERROR!!!") + " " + (messageString)) \

#define WRITE_ERROR_WITH_PARAMS(logger, messageString, ...) \
	WRITE_PROD(logger, string("ERROR!!!") + " " + (messageString), __VA_ARGS__) \

#define WRITE_DEBUG(logger, messageString) \
	WRITE_LOG(logger, messageString, ELogLevel::DEBUG) \

#define WRITE_DEBUG_WITH_PARAMS(logger, messageString, ...) \
	WRITE_LOG_WITH_PARAMS(logger, messageString, ELogLevel::DEBUG, __VA_ARGS__) \

#define WRITE_PROD_EXCEPTION(logger, exception) \
	WRITE_LOG_EXCEPTION(logger, exception, ELogLevel::DEBUG) \

#define WRITE_TRACE(logger, messageString) \
	WRITE_LOG(logger, messageString, ELogLevel::TRACE) \

#define WRITE_TRACE_WITH_PARAMS(logger, messageString, ...) \
	WRITE_LOG_WITH_PARAMS(logger, messageString, ELogLevel::TRACE, __VA_ARGS__) \

#define WRITE_PROD_EXCEPTION(logger, exception) \
	WRITE_LOG_EXCEPTION(logger, exception, ELogLevel::TRACE) \
