#pragma once
#include "CLogger/include/stdafx.h"

#include "CLogBuilder/CLogBuilder.h"

namespace CLog {
	inline std::unique_ptr<CLogBuilder> loggerBuilder = std::unique_ptr<CLogBuilder>(nullptr);
	inline std::unique_ptr<CLogger> logger = std::unique_ptr<CLogger>(nullptr);

	inline std::mutex loggerBuilderMutex = std::mutex();
	inline std::mutex loggerMutex = std::mutex();
	
	inline std::unique_ptr<CLogBuilder>& GetBuilder() {
		return loggerBuilder;
	}

	inline std::unique_ptr<CLogger>& GetLogger() {
		return logger;
	}

	inline void SetBuilder(std::unique_ptr<CLogBuilder>&& build) {
		std::unique_lock<std::mutex> lock(loggerBuilderMutex);
		loggerBuilder = std::move(build);
	}

	inline void SetLogger(std::unique_ptr<CLogger>&& log) {
		std::unique_lock<std::mutex> lock(loggerMutex);
		logger = std::move(log);
	}
}
