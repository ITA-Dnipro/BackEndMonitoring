#pragma once
#include "CLogBuilder/CLogBuilder.h"

extern auto loggerBuilder = std::unique_ptr<CLogBuilder>(nullptr);
extern auto logger = std::unique_ptr<CLogger>(nullptr);

#define CLOG_START_CREATION() \
	loggerBuilder = std::move(std::make_unique<CLogBuilder>("", ELogLevel::NONE_LEVEL)) \

#define CLOG_END_CREATION() \
	loggerBuilder.reset() \

#define CLOG_ADD_SAFE_STREAM(stream) \
	loggerBuilder->AddThreadSafeStream(stream) \

#define CLOG_ADD_UNSAFE_STREAM(stream) \
	loggerBuilder->AddThreadUnsafeStream(stream) \

#define CLOG_SET_LOG_NAME(logName) \
	loggerBuilder->SetLogName(logName) \

#define CLOG_SET_LOG_LEVEL(logLevel) \
	loggerBuilder->SetLogLevel(logLevel) \

#define CLOG_SET_LOG_CONFIG(...) \
	loggerBuilder->SetLogConfig(__VA_ARGS__) \

#define CLOG_ADD_LOG_CONFIG(logConfig) \
	loggerBuilder->AddLogConfig(logConfig) \

#define CLOG_BUILD() \
	logger = std::move(loggerBuilder->BuildUniqueLog()) \

#define CLOG_DESTROY() \
	logger.reset() \
