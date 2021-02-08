#pragma once
#include "CLogBuilder/CLogBuilder.h"
#include "CLoggerGlobal/GlobalLogger.h"

#define CLOG_EDIT_ADD_SAFE_STREAM(stream) \
	CLog::GetLogger()->AddThreadSafeStream(stream) \

#define CLOG_EDIT_ADD_UNSAFE_STREAM(stream) \
	CLog::GetLogger()->AddThreadUnsafeStream(stream) \

#define CLOG_EDIT_SET_LOG_NAME(logName) \
	CLog::GetLogger()->SetLogName(logName) \

#define CLOG_EDIT_SET_LOG_FLUSH(logFlush) \
	CLog::GetLogger()->SetLogFlush(logFlush) \

#define CLOG_EDIT_SET_LOG_LEVEL(logLevel) \
	CLog::GetLogger()->SetLogLevel(logLevel) \

#define CLOG_EDIT_SET_NONE() \
	CLOG_EDIT_SET_LOG_LEVEL(ELogLevel::NONE_LEVEL) \

#define CLOG_EDIT_SET_PROD() \
	CLOG_EDIT_SET_LOG_LEVEL(ELogLevel::PROD_LEVEL) \

#define CLOG_EDIT_SET_DEBUG() \
	CLOG_EDIT_SET_LOG_LEVEL(ELogLevel::DEBUG_LEVEL) \

#define CLOG_EDIT_SET_TRACE() \
	CLOG_EDIT_SET_LOG_LEVEL(ELogLevel::TRACE_LEVEL) \

#define CLOG_EDIT_SET_LOG_CONFIG(...) \
	CLog::GetLogger()->SetLogConfig(__VA_ARGS__) \

#define CLOG_EDIT_ADD_LOG_CONFIG(logConfig) \
	CLog::GetLogger()->AddLogConfig(logConfig) \

#define CLOG_EDIT_ADD_LOG_LEVEL() \
	CLOG_EDIT_ADD_LOG_CONFIG(ELogConfig::LOG_LEVEL) \

#define CLOG_EDIT_ADD_LOG_NAME() \
	CLOG_EDIT_ADD_LOG_CONFIG(ELogConfig::LOG_NAME) \

#define CLOG_EDIT_ADD_LINE_NUMBER() \
	CLOG_EDIT_ADD_LOG_CONFIG(ELogConfig::LINE_NUMBER) \

#define CLOG_EDIT_ADD_FILE_NAME() \
	CLOG_EDIT_ADD_LOG_CONFIG(ELogConfig::FILE_NAME) \

#define CLOG_EDIT_ADD_FUNCTION_NAME() \
	CLOG_EDIT_ADD_LOG_CONFIG(ELogConfig::FUNCTION_NAME) \

#define CLOG_EDIT_ADD_THREAD_ID() \
	CLOG_EDIT_ADD_LOG_CONFIG(ELogConfig::THREAD_ID) \

#define CLOG_EDIT_ADD_CALL_TIME() \
	CLOG_EDIT_ADD_LOG_CONFIG(ELogConfig::CALL_TIME) \

#define CLOG_EDIT_ADD_MESSAGE() \
	CLOG_EDIT_ADD_LOG_CONFIG(ELogConfig::MESSAGE) \

#define CLOG_EDIT_ADD_PARAMS() \
	CLOG_EDIT_ADD_LOG_CONFIG(ELogConfig::PARAMS)
