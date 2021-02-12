#pragma once
#include "stdafx.h"

#include "CLogBuilder/CLogBuilder.h"

class CLOGGER_API CLoggerWrapper
{
public:
	//CLoggerWrapper() = default;
	CLoggerWrapper(const CLoggerWrapper&)     = delete;
	CLoggerWrapper(CLoggerWrapper&&) noexcept = default;
	
	~CLoggerWrapper() = default;
	
	CLoggerWrapper& operator=(const CLoggerWrapper&) = delete;
	CLoggerWrapper& operator=(CLoggerWrapper&&) noexcept = default;

	static std::unique_ptr<CLogBuilder>& GetBuilder();
	static std::unique_ptr<CLogger>& GetLogger();
	
	static void SetBuilder(std::unique_ptr<CLogBuilder>&& build);
	static void SetLogger(std::unique_ptr<CLogger>&& log);
	
	static void ResetBuilder();
	static void ResetLogger();

private:
	static std::unique_ptr<CLogger> logger_;
	//static std::mutex logger_mutex_;
	
	static std::unique_ptr<CLogBuilder> logger_builder_;
	//static std::mutex logger_builder_mutex_;
};

extern CLOGGER_API std::unique_ptr<CLoggerWrapper> global_logger_wrapper;
