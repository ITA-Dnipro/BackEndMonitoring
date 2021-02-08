#pragma once
#include "CLogBuilder/CLogBuilder.h"
#include "CLoggerGlobal/GlobalLogger.h"

#define CLOG_START_CREATION() \
	CLog::SetBuilder(std::move(std::make_unique<CLogBuilder>("", ELogLevel::NONE_LEVEL))) \

#define CLOG_END_CREATION() \
	CLog::GetBuilder().reset() \

#define CLOG_ADD_SAFE_STREAM(stream) \
	CLog::GetBuilder()->AddThreadSafeStream(stream) \

#define CLOG_ADD_UNSAFE_STREAM(stream) \
	CLog::GetBuilder()->AddThreadUnsafeStream(stream) \

#define CLOG_SET_LOG_NAME(logName) \
	CLog::GetBuilder()->SetLogName(logName) \

#define CLOG_SET_LOG_FLUSH(logFlush) \
	CLog::GetBuilder()->SetLogFlush(logFlush) \

#define CLOG_SET_LOG_LEVEL(logLevel) \
	CLog::GetBuilder()->SetLogLevel(logLevel) \

#define CLOG_SET_LOG_CONFIG(...) \
	CLog::GetBuilder()->SetLogConfig(__VA_ARGS__) \

#define CLOG_ADD_LOG_CONFIG(logConfig) \
	CLog::GetBuilder()->AddLogConfig(logConfig) \

#define CLOG_ADD_LOG_LEVEL() \
	CLog::GetBuilder()->AddLogConfig(ELogConfig::LOG_LEVEL) \

#define CLOG_ADD_LOG_NAME() \
	CLog::GetBuilder()->AddLogConfig(ELogConfig::LOG_NAME) \

#define CLOG_ADD_LINE_NUMBER() \
	CLog::GetBuilder()->AddLogConfig(ELogConfig::LINE_NUMBER) \

#define CLOG_ADD_FILE_NAME() \
	CLog::GetBuilder()->AddLogConfig(ELogConfig::FILE_NAME) \

#define CLOG_ADD_FUNCTION_NAME() \
	CLog::GetBuilder()->AddLogConfig(ELogConfig::FUNCTION_NAME) \

#define CLOG_ADD_THREAD_ID() \
	CLog::GetBuilder()->AddLogConfig(ELogConfig::THREAD_ID) \

#define CLOG_ADD_CALL_TIME() \
	CLog::GetBuilder()->AddLogConfig(ELogConfig::CALL_TIME) \

#define CLOG_ADD_MESSAGE() \
	CLog::GetBuilder()->AddLogConfig(ELogConfig::MESSAGE) \

#define CLOG_ADD_PARAMS() \
	CLog::GetBuilder()->AddLogConfig(ELogConfig::PARAMS) \

#define CLOG_BUILD() \
	CLog::SetLogger(std::move(CLog::GetBuilder()->BuildUniqueLog())) \

#define CLOG_DESTROY() \
	CLog::GetLogger().reset()
