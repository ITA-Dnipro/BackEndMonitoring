#pragma once
#include "stdafx.h"

#include "ELogConfig/ELogConfig.h"
#include "ELogLevel/ELogLevel.h"
#include "CLogMessage/CLogMessage.h"


/// <summary>
///		Class to output <c>CLogMessage</c>
/// </summary>
class CLOGGER_API CLogger
{
public:
	CLogger() = delete;
	explicit CLogger(const std::string& log_name, ELogLevel log_level);
	CLogger(const CLogger&) = delete;
	CLogger(CLogger&&) noexcept;

	~CLogger() noexcept;

	CLogger& AddThreadSafeStream(std::ostream& stream);
	CLogger& AddThreadUnsafeStream(std::ostream& stream);

	[[nodiscard]] ELogLevel GetLogLevel() const;
	CLogger& SetLogLevel(ELogLevel log_level);

	[[nodiscard]] std::string GetLogName() const;

	template<typename... Args>
	CLogger& SetLogConfig(Args... args);
	
	template<class ... Args>
	CLogger& AddLogConfig(ELogConfig log_config, Args... args);
	CLogger& AddLogConfig(ELogConfig log_config);

	template<typename... Args>
	void PrintLogMessage(const CLogMessage<Args...>& log_message) const;

	void PrintLogInfo() const;

	CLogger& operator=(const CLogger&) = delete;
	CLogger& operator=(CLogger&&) noexcept;

private:
	ELogLevel m_log_level;
	std::string m_log_name;
	std::list<ELogConfig> m_log_config_list;
	std::list<std::pair<std::reference_wrapper<std::ostream>,
		std::unique_ptr<std::mutex>>> m_write_stream_list;

	template<typename... Args>
	void PrintToAllStreams(const CLogMessage<Args...>& log_message) const;
	
	template<typename... Args>
	std::ostream& PrintLogMessage(const CLogMessage<Args...>& log_message,
		std::ostream& stream) const;

	template<typename... Args>
	std::ostream& PrintParams(const CLogMessage<Args...>& log_message,
		std::ostream& stream) const;
	template<typename TupleType, size_t... Size>
	std::ostream& PrintParams(const TupleType& tuple,
		std::index_sequence<Size...>, std::ostream& stream) const;

	void PrintToAllStreams(const std::string& info) const;
	std::ostream& PrintLogInfo(const std::string& info,
		std::ostream& stream) const;
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
	m_log_config_list.clear();
	AddLogConfig(args...);
	
	return *this;
}

template<typename... Args>
CLogger& CLogger::AddLogConfig(const ELogConfig log_config, Args... args)
{
	if (std::find(m_log_config_list.begin(),
		m_log_config_list.end(), log_config) == m_log_config_list.end())
	{
		m_log_config_list.emplace_back(log_config);
	}

	return AddLogConfig(args...);
}

/// <summary>
///		Prints to all streams, that <c>CLogger</c> stores, <c>CLogMessage</c> object
/// </summary>
/// <typeparam name="...Args">
///		Variadic template types of <c>CLogMessage</c>
///	</typeparam>
/// <param name="log_message">
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
void CLogger::PrintLogMessage(const CLogMessage<Args...>& log_message) const
{
	if (m_log_level < log_message.GetLogLevel()
		|| m_write_stream_list.empty()
		|| m_log_config_list.empty())
	{
		return;
	}

	PrintToAllStreams(log_message);
}

/// <summary>
///		Prints some <c>CLogMessage</c> to all
///		output streams of <c>CLogger</c>
/// </summary>
/// <typeparam name="...Args">
///		
/// </typeparam>
/// <param name="log_message">
///		<c>CLogMessage</c> to print
/// </param>
template<typename ... Args>
void CLogger::PrintToAllStreams(const CLogMessage<Args...>& log_message) const
{
	for (const auto& [stream, mutex] : m_write_stream_list)
	{
		auto unique_lock = nullptr == mutex ?
			std::unique_lock<std::mutex>() :
			std::unique_lock<std::mutex>(*mutex);
		
		PrintLogMessage(log_message, stream);
	}
}

/// <summary>
///		Prints to one stream <c>CLogMessage</c> object
/// </summary>
/// <typeparam name="...Args">
///		Variadic template types of <c>CLogMessage</c>	
/// </typeparam>
/// <param name="log_message">
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
std::ostream& CLogger::PrintLogMessage(const CLogMessage<Args...>& log_message,
	std::ostream& stream) const
{
	std::stringstream ss;

	for (const auto& config : m_log_config_list)
	{
		switch (config)
		{
			// TODO different delimiters and scopes
			// TODO remove repeat-code
			// TODO config flush
		case ELogConfig::THREAD_ID:
		{
			ss << "Thread id:" << " " << "[" << log_message.GetThreadId()
				<< "]" << " " << std::flush;
			break;
		}
		case ELogConfig::CALL_TIME:
		{
			ss << "Time:" << " " << "[" << log_message.GetTimeString()
				<< "]" << " " << std::flush;
			break;
		}
		case ELogConfig::FUNCTION_NAME:
		{
			ss << "Function:" << " " << log_message.GetFunctionString()
				<< " " << std::flush;
			break;
		}
		case ELogConfig::FILE_NAME:
		{
			ss << "File:" << " " << log_message.GetFileString()
				<< " " << std::flush;
			break;
		}
		case ELogConfig::LINE_NUMBER:
		{
			ss << "Line number:" << " " << log_message.GetLineNumber()
				<< " " << std::flush;
			break;
		}
		case ELogConfig::MESSAGE:
		{
			ss << "Message:" << " " << log_message.GetMessageString()
				<< " " << std::flush;
			break;
		}
		case ELogConfig::LOG_LEVEL:
		{
			ss << "[" << LogLevelToString(log_message.GetLogLevel())
				<< "]" << " " << std::flush;
			break;
		}
		case ELogConfig::PARAMS:
		{
			PrintParams(log_message, ss);
			ss << std::flush;
			break;
		}
		case ELogConfig::LOG_NAME:
		{
			ss << m_log_name << " " << std::flush;
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
/// <param name="log_message">
///		<c>CLogMessage</c> with parameters to print
/// </param>
/// <param name="stream">
///		Output stream to out data
/// </param>
/// <returns>
///		Reference to output stream
/// </returns>
template<typename... Args>
std::ostream& CLogger::PrintParams(const CLogMessage<Args...>& log_message,
	std::ostream& stream) const
{
	auto temp = log_message.GetParams();

	if (0u == std::tuple_size<decltype(temp)>::value)
	{
		return stream;
	}

	return PrintParams(temp, std::make_index_sequence<sizeof...(Args)>(), stream) << " ";
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