#pragma once
#include "../CLogBuilder/CLogBuilder.h"
#include "../GlobalLogger.h"

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

#define CLOG_BUILD() \
	CLog::SetLogger(std::move(CLog::GetBuilder()->BuildUniqueLog())) \

#define CLOG_DESTROY() \
	CLog::GetLogger().reset()
