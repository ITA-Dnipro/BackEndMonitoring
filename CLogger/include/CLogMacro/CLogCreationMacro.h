#pragma once
#include "stdafx.h"

#define CLOG_START_CREATION(loggerName, logLevel) \
	loggerBuilder = std::make_unique<CLogBuilder>(loggerName, logLevel); \

#define CLOG_END_CREATION() \
	loggerBuilder.reset(); \

#define CLOG_ADD_SAFE_STREAM(stream) \
	loggerBuilder->AddThreadSafeStream(stream); \

#define CLOG_ADD_UNSAFE_STREAM(stream) \
	loggerBuilder->AddThreadUnsafeStream(stream); \

#define CLOG_SET_LOG_CONFIG(...) \
	loggerBuilder->SetLogConfig(__VA_ARGS__); \

#define CLOG_ADD_LOG_CONFIG(logConfig) \
	loggerBuilder->AddLogConfig(logConfig); \

#define CLOG_BUILD() \
	logger = loggerBuilder->BuildUniqueLog(); \

#define CLOG_DESTROY() \
	logger.reset(); \
