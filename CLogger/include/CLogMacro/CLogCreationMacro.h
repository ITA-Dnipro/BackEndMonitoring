#pragma once
#include "CLogBuilder/CLogBuilder.h"
#include "CLoggerGlobal/GlobalLogger.h"

#define CLOG_CREATION_START() \
	CLog::SetBuilder(std::move(std::make_unique<CLogBuilder>("", ELogLevel::NONE_LEVEL))) \

#define CLOG_CREATION_END() \
	CLog::GetBuilder().reset() \

#define CLOG_CREATION_ADD_SAFE_STREAM(stream) \
	CLog::GetBuilder()->AddThreadSafeStream(stream) \

#define CLOG_CREATION_ADD_UNSAFE_STREAM(stream) \
	CLog::GetBuilder()->AddThreadUnsafeStream(stream) \

#define CLOG_CREATION_SET_LOG_NAME(logName) \
	CLog::GetBuilder()->SetLogName(logName) \

#define CLOG_CREATION_SET_LOG_FLUSH(logFlush) \
	CLog::GetBuilder()->SetLogFlush(logFlush) \

#define CLOG_CREATION_SET_LOG_LEVEL(logLevel) \
	CLog::GetBuilder()->SetLogLevel(logLevel) \

#define CLOG_CREATION_SET_NONE() \
	CLOG_CREATION_SET_LOG_LEVEL(ELogLevel::NONE_LEVEL) \

#define CLOG_CREATION_SET_PROD() \
	CLOG_CREATION_SET_LOG_LEVEL(ELogLevel::PROD_LEVEL) \

#define CLOG_CREATION_SET_DEBUG() \
	CLOG_CREATION_SET_LOG_LEVEL(ELogLevel::DEBUG_LEVEL) \

#define CLOG_CREATION_SET_TRACE() \
	CLOG_CREATION_SET_LOG_LEVEL(ELogLevel::TRACE_LEVEL) \

#define CLOG_CREATION_SET_LOG_CONFIG(...) \
	CLog::GetBuilder()->SetLogConfig(__VA_ARGS__) \

#define CLOG_CREATION_ADD_LOG_CONFIG(logConfig) \
	CLog::GetBuilder()->AddLogConfig(logConfig) \

#define CLOG_CREATION_ADD_LOG_LEVEL() \
	CLOG_CREATION_ADD_LOG_CONFIG(ELogConfig::LOG_LEVEL) \

#define CLOG_CREATION_ADD_LOG_NAME() \
	CLOG_CREATION_ADD_LOG_CONFIG(ELogConfig::LOG_NAME) \

#define CLOG_CREATION_ADD_LINE_NUMBER() \
	CLOG_CREATION_ADD_LOG_CONFIG(ELogConfig::LINE_NUMBER) \

#define CLOG_CREATION_ADD_FILE_NAME() \
	CLOG_CREATION_ADD_LOG_CONFIG(ELogConfig::FILE_NAME) \

#define CLOG_CREATION_ADD_FUNCTION_NAME() \
	CLOG_CREATION_ADD_LOG_CONFIG(ELogConfig::FUNCTION_NAME) \

#define CLOG_CREATION_ADD_THREAD_ID() \
	CLOG_CREATION_ADD_LOG_CONFIG(ELogConfig::THREAD_ID) \

#define CLOG_CREATION_ADD_CALL_TIME() \
	CLOG_CREATION_ADD_LOG_CONFIG(ELogConfig::CALL_TIME) \

#define CLOG_CREATION_ADD_MESSAGE() \
	CLOG_CREATION_ADD_LOG_CONFIG(ELogConfig::MESSAGE) \

#define CLOG_CREATION_ADD_PARAMS() \
	CLOG_CREATION_ADD_LOG_CONFIG(ELogConfig::PARAMS) \

#define CLOG_BUILD() \
	CLog::SetLogger(std::move(CLog::GetBuilder()->BuildUniqueLog())) \

#define CLOG_DESTROY() \
	CLog::GetLogger().reset()
