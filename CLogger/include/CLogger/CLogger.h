#pragma once
#include "stdafx.h"

#include <list>
#include <ostream>
#include <sstream>

#include "ELogConfig/ELogConfig.h"
#include "ELogLevel/ELogLevel.h"
#include "CLogMessage/CLogMessage.h"

/// <summary>
/// Class to output <c>CLogMessage</c>
/// </summary>
class CLOGGER_API CLogger
{
public:
	CLogger() = delete;
	explicit CLogger(const std::string& logName, ELogLevel logLevel);
	CLogger(const CLogger&) = delete;
	CLogger(CLogger&&) noexcept;

	~CLogger() noexcept;

	CLogger& AddStream(std::ostream& stream);

	[[nodiscard]] ELogLevel GetLogLevel() const;
	CLogger& SetLogLevel(ELogLevel logLevel);

	[[nodiscard]] std::string GetLogName() const;

	template<typename... Args>
	CLogger& SetLogConfig(Args... args);
	CLogger& AddLogConfig(ELogConfig logConfig);

	template<typename... Args>
	void PrintLogMessage(const CLogMessage<Args...>& logMessage) const;

	void PrintLogInfo() const;

	CLogger& operator=(const CLogger&) = delete;
	CLogger& operator=(CLogger&&) noexcept;

private:
	ELogLevel m_log_level;
	std::string m_log_name;
	std::list<ELogConfig> m_log_config_list;
	std::list<std::reference_wrapper<std::ostream>> m_write_stream_list;
	//mutex logMutex_;

	template<typename... Args>
	std::ostream& PrintLogMessage(const CLogMessage<Args...>& logMessage, std::ostream& stream) const;

	template<typename... Args>
	std::ostream& PrintParams(const CLogMessage<Args...>& logMessage, std::ostream& stream) const;
	template<typename TupleType, size_t... Size>
	std::ostream& PrintParams(const TupleType& tuple, std::index_sequence<Size...>, std::ostream& stream) const;

	std::ostream& PrintLogInfo(const std::string& info, std::ostream& stream) const;
};

/// <summary>
///		Clears all <c>ELogConfig</c> that was stored at <c>CLogger</c>
///		And than adds endless amount of <c>ELogConfig</c>. Order is important.
///		Duplicates will be ignored.
/// </summary>
/// <typeparam name="...Args">
///		Variadic template types. Waits just for <c>ELogConfig</c>.
///	</typeparam>
/// <param name="args">
///		Variadic template parameters. Waits just for <c>ELogConfig</c> instances.
/// </param>
/// <returns>
///		Reference to <c>this</c> object
///		to continue work with class methods in one line
/// </returns>
/// <example>
///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG);
///		auto* testLogger = testBuilder->Build();
///		testLogger->SetLogConfig(ELogConfig::MESSAGE, ELogConfig::LOG_LEVEL,
///		ELogConfig::PARAMS, ELogConfig::MESSAGE /* won't be added */);
/// </example>
template<typename... Args>
CLogger& CLogger::SetLogConfig(Args... args)
{
	this->m_log_config_list.clear();
	this->AddLogConfig(args...);
	return *this;
}

/// <summary>
///		Prints to all streams, that <c>CLogger</c> stores, <c>CLogMessage</c> object
/// </summary>
/// <typeparam name="...Args">
///		Variadic template types of <c>CLogMessage</c>
///	</typeparam>
/// <param name="logMessage">
///		<c>CLogMessage</c> to print
/// </param>
/// <example>
///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG);
///		auto* testLogger = testBuilder->Build();
///		testLogger->SetLogConfig(ELogConfig::MESSAGE, ELogConfig::LOG_LEVEL,
///		ELogConfig::PARAMS);
///		testLogger->PrintLogMessage(CLogMessage(/*...*/));
/// </example>
template<typename... Args>
void CLogger::PrintLogMessage(const CLogMessage<Args...>& logMessage) const
{
	// TODO: method
	if (this->m_log_level < logMessage.GetLogLevel()) {
		return;
	}

	// TODO: method to out all data to all stream
	for (const auto& stream : this->m_write_stream_list) {
		this->PrintLogMessage(logMessage, stream);
	}
}

/// <summary>
/// </summary>
/// <typeparam name="...Args">
///		Variadic template types of <c>CLogMessage</c>
///	</typeparam>
/// <param name="logMessage">
///		<c>CLogMessage</c> to print
/// </param>
/// <example>
///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG);
///		auto* testLogger = testBuilder->Build();
///		testLogger->SetLogConfig(ELogConfig::MESSAGE, ELogConfig::LOG_LEVEL,
///		ELogConfig::PARAMS);
///		testLogger->PrintLogMessage(CLogMessage(/*...*/));
/// </example>

/// <summary>
///		Prints to one stream <c>CLogMessage</c> object
/// </summary>
/// <typeparam name="...Args">
///		Variadic template types of <c>CLogMessage</c>	
/// </typeparam>
/// <param name="logMessage">
///		<c>CLogMessage</c> to print
/// </param>
/// <param name="stream">
///		Output stream such as <c>std::cout</c>, <c>std::cerr</c>
///		or instance of <c>std::ofstream</c>
/// </param>
/// <returns>
///		Modified output stream
/// </returns>
template<typename... Args>
std::ostream& CLogger::PrintLogMessage(const CLogMessage<Args...>& logMessage, std::ostream& stream) const {
	std::stringstream ss;

	for (const auto& config : this->m_log_config_list)
	{
		switch (config)
		{
			// TODO different delimiters and scopes
			// TODO remove repeat-code
			// TODO config flush
		case ELogConfig::THREAD_ID:
		{
			ss << "Thread id:" << " " << "[" << logMessage.GetThreadId()
				<< "]" << " " << std::flush;
			break;
		}
		case ELogConfig::CALL_TIME:
		{
			ss << "Time:" << " " << "[" << logMessage.GetTimeString()
				<< "]" << " " << std::flush;
			break;
		}
		case ELogConfig::FUNCTION_NAME:
		{
			ss << "Function:" << " " << logMessage.GetFunctionString()
				<< " " << std::flush;
			break;
		}
		case ELogConfig::FILE_NAME:
		{
			ss << "File:" << " " << logMessage.GetFileString()
				<< " " << std::flush;
			break;
		}
		case ELogConfig::LINE_NUMBER:
		{
			ss << "Line number:" << " " << logMessage.GetLineNumber()
				<< " " << std::flush;
			break;
		}
		case ELogConfig::MESSAGE:
		{
			ss << std::endl << "Message:" << " " << logMessage.GetMessageString()
				<< " " << std::flush;
			break;
		}
		case ELogConfig::LOG_LEVEL:
		{
			ss << "[" << LogLevelToString(logMessage.GetLogLevel())
				<< "]" << " " << std::flush;
			break;
		}
		case ELogConfig::PARAMS:
		{
			this->PrintParams(logMessage, ss);
			ss << std::flush;
			break;
		}
		case ELogConfig::LOG_NAME:
		{
			ss << this->m_log_name << " " << std::flush;
			break;
		}
		case ELogConfig::NONE:
		{
			break;
		}
		}
	}

	// TODO remove last char " "
	return stream << ss.str() << std::endl;
}

/// <summary>
///		Prints <c>CLogMessage</c> parameters
/// </summary>
/// <typeparam name="...Args">
///		Variadic template types of <c>CLogMessage</c>
/// </typeparam>
/// <param name="logMessage">
///		<c>CLogMessage</c> with parameters to print
/// </param>
/// <param name="stream">
///		Output stream to out data
/// </param>
/// <returns>
///		Reference to output stream
/// </returns>
template<typename... Args>
std::ostream& CLogger::PrintParams(const CLogMessage<Args...>& logMessage,
	std::ostream& stream) const
{
	auto temp = logMessage.GetParams();

	if (0u == std::tuple_size<decltype(temp)>::value)
	{
		return stream;
	}

	return this->PrintParams(temp, std::make_index_sequence<sizeof...(Args)>(), stream) << " ";
}

/// <summary>
///		Prints <c>std::tuple</c> of <c>CLogMessage</c>
/// </summary>
/// <typeparam name="TupleType">
///		Type of <c>std::tuple</c>
/// </typeparam>
/// <param name="tuple">
///		<c>std::tuple</c> to print
/// </param>
/// <param name="index">
///		<c>std::tuple</c> element count
/// </param>
/// <param name="stream">
///		Output stream to out data
///	</param>
/// <returns>
///		Reference to output stream
/// </returns>
template<typename TupleType, size_t ...Size>
std::ostream& CLogger::PrintParams(const TupleType& tuple,
	std::index_sequence<Size...> index, std::ostream& stream) const
{
	(..., (stream << (0u == Size ? "" : ", ") << std::get<Size>(tuple).first << " "
		<< "=" << " " << std::get<Size>(tuple).second));

	return stream;
}