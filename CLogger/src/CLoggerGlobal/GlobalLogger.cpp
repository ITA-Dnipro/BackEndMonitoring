#include "stdafx.h"

#include "CLoggerGlobal/GlobalLogger.h"

std::unique_ptr<CLoggerWrapper> global_logger_wrapper = nullptr;
std::unique_ptr<CLogger> CLoggerWrapper::logger_ = nullptr;
std::unique_ptr<CLogBuilder> CLoggerWrapper::logger_builder_ = nullptr;

std::unique_ptr<CLogBuilder>& CLoggerWrapper::GetBuilder() {
	if (nullptr == logger_builder_) {
		//std::unique_lock<std::mutex> lock(logger_builder_mutex_);
		logger_builder_ =
			std::make_unique<CLogBuilder>
			("", ELogLevel::NONE_LEVEL, ELogFlush::NOT_FLUSH);
	}

	return logger_builder_;
}

std::unique_ptr<CLogger>& CLoggerWrapper::GetLogger() {
	if (nullptr == logger_) {
		//std::unique_lock<std::mutex> lock(logger_mutex_);
		logger_ = GetBuilder()->BuildUniqueLog();
	}

	return logger_;
}

void CLoggerWrapper::SetBuilder(std::unique_ptr<CLogBuilder>&& build) {
	//std::unique_lock<std::mutex> lock(logger_builder_mutex_);
	logger_builder_ = std::move(build);
}

void CLoggerWrapper::SetLogger(std::unique_ptr<CLogger>&& log) {
	//std::unique_lock<std::mutex> lock(logger_mutex_);
	logger_ = std::move(log);
}

void CLoggerWrapper::ResetBuilder() {
	logger_builder_.reset();
}

void CLoggerWrapper::ResetLogger() {
	logger_.reset();
}
