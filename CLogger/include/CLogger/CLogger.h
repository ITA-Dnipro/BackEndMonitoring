#pragma once
#include "stdafx.h"

#include <functional>

#include "ELogConfig/ELogConfig.h"
#include "ELogLevel/ELogLevel.h"
#include "ELogFlush/ELogFlush.h"
#include "CLogMessage/CLogMessage.h"

/// <summary>
///		Class to output <c>CLogMessage</c>
/// </summary>
class CLOGGER_API CLogger
{
public:
	CLogger() = delete;
	/// <summary>
	///		Explicit two-parameter ctor, that initializes
	///		name and <c>ELogLevel</c> of <c>CLogger</c>
	/// </summary>
	/// <param name="log_name">
	///		Unique name of <c>CLogger</c> instance</param>
	/// </param>
	/// <param name="log_level">
	///		<c>ELogLevel</c> of <c>CLogger</c>,
	///		which helps to filter out some messages
	/// </param>
	/// <example>
	///		const auto* testLogger = new CLogger("TestName", ELogLevel::DEBUG_LEVEL));
	/// </example>
	explicit CLogger(const std::string& log_name, ELogLevel log_level);
	explicit CLogger(const std::string& log_name, ELogLevel log_level, ELogFlush log_flush);
	CLogger(const CLogger&) = delete;
	/// <summary>
	///		Default move ctor for <c>CLogBuilder</c>
	/// </summary>
	/// <param name="move">
	///		Rvalue reference to <c>CLogger</c>
	/// </param>
	/// <example>
	///		auto* testLogger1       = new CLogger("TestName", ELogLevel::DEBUG_LEVEL);
	///		const auto* testLogger2 = new CLogger(std::move(*testLogger1));
	/// </example>
	CLogger(CLogger&& move) noexcept;

	/// <summary>
	///		Default dtor of <c>CLogger</c>
	/// </summary>
	~CLogger() noexcept;

	/// <summary>
	///		Adds thread safe (with <c>std::mutex</c>) output stream of <c>CLogger</c>.
	///		<c>CLogger</c> doesn't own the stream, so it won't call there dtors
	/// </summary>
	/// <param name="stream">
	///		Output stream such as <c>std::cout</c>, <c>std::cerr</c>
	///		or instance of <c>std::ofstream</c>
	///	</param>
	/// <returns>
	///		Reference to <c>this</c> object
	///		to continue work with class methods in one line
	/// </returns>
	/// <example>
	///		std::ofstream testFile("TestFile.txt");
	///		auto* testLogger1 = new CLogger("TestName", ELogLevel::DEBUG_LEVEL);
	///		testLogger1->AddStream(std::cout).AddStream(testFile);
	/// </example>
	CLogger& AddThreadSafeStream(std::ostream& stream);
	/// <summary>
	///		Adds thread unsafe (without <c>std::mutex</c>) output stream of
	///		<c>CLogger</c>. <c>CLogger</c> doesn't own the stream,
	///		so it won't call there dtors
	/// </summary>
	/// <param name="stream">
	///		Output stream such as <c>std::cout</c>, <c>std::cerr</c>
	///		or instance of <c>std::ofstream</c>
	///	</param>
	/// <returns>
	///		Reference to <c>this</c> object
	///		to continue work with class methods in one line
	/// </returns>
	/// <example>
	///		std::ofstream testFile("TestFile.txt");
	///		auto* testLogger1 = new CLogger("TestName", ELogLevel::DEBUG_LEVEL);
	///		testLogger1->AddThreadUnsafeStream(std::cout)
	///			.AddThreadUnsafeStream(testFile, mtx);
	/// </example>
	CLogger& AddThreadUnsafeStream(std::ostream& stream);

	/// <summary>
	///		<c>ELogLevel</c> getter
	/// </summary>
	/// <returns>
	///		<c>ELogLevel</c>, which helps to filter out some messages
	/// </returns>
	/// <example>
	///		const auto* testLogger = new CLogger("TestName", ELogLevel::DEBUG_LEVEL);
	///		ELogLevel test = testLogger->GetLogLevel();
	/// </example>
	[[nodiscard]] ELogLevel GetLogLevel() const;
	/// <summary>
	///		<c>ELogLevel</c> setter
	/// </summary>
	/// <param name="log_level">
	///		<c>ELogLevel</c> to set
	///	</param>
	/// <returns>
	///		Reference to <c>this</c> object
	///		to continue work with class methods in one line
	/// </returns>
	/// <example>
	///		const auto* testLogger = new CLogger("TestName", ELogLevel::DEBUG_LEVEL);
	///		testLogger->SetLogLevel(ELogLevel::TRACE_LEVEL);
	/// </example>
	CLogger& SetLogLevel(ELogLevel log_level);

	/// <summary>
	///		<c>ELogFlush</c> getter
	/// </summary>
	/// <returns>
	///		<c>ELogFlush</c>, which indicates if output stream flushes
	/// </returns>
	/// <example>
	///		const auto* testLogger = new CLogger("TestName", ELogLevel::DEBUG_LEVEL,
	///			ELogFlush::FLUSH);
	///		ELogFlush test = testLogger->GetLogFlush();
	/// </example>
	[[nodiscard]] ELogFlush GetLogFlush() const;
	/// <summary>
	///		<c>ELogFlush</c> setter
	/// </summary>
	/// <param name="log_flush">
	///		<c>ELogFlush</c> to set
	///	</param>
	/// <returns>
	///		Reference to <c>this</c> object
	///		to continue work with class methods in one line
	/// </returns>
	/// <example>
	///		const auto* testLogger = new CLogger("TestName", ELogLevel::DEBUG_LEVEL,
	///			ELogFlush::FLUSH);
	///		testLogger->SetLogFlush(ELogLevel::NOT_FLUSH);
	/// </example>
	CLogger& SetLogFlush(ELogFlush log_flush);

	/// <summary>
	///		Name of <c>CLogger</c> getter
	/// </summary>
	/// <returns>
	///		Unique name of <c>CLogger</c>
	/// </returns>
	/// <example>
	///		const auto* testLogger = new CLogger("TestName", ELogLevel::DEBUG_LEVEL);
	///		std::string name = testLogger->GetLogName();
	/// </example>
	[[nodiscard]] std::string GetLogName() const;

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
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG_LEVEL);
	///		auto* testLogger = testBuilder->Build();
	///		testLogger->SetLogConfig(ELogConfig::MESSAGE, ELogConfig::LOG_LEVEL,
	///		ELogConfig::PARAMS, ELogConfig::MESSAGE /* won't be added */);
	/// </example>
	template<typename... Args>
	CLogger& SetLogConfig(Args... args);

	template<class ... Args>
	CLogger& AddLogConfig(ELogConfig log_config, Args... args);
	/// <summary>
	///		Adds a single <c>ELogConfig</c> of <c>CLogger</c> setter.
	///		The order of addition is important for output string of
	///		<c>CLogger</c>. Also it ignores duplicates
	/// </summary>
	/// <param name="log_config">
	///		<c>ELogConfig</c> that modifies output string of <c>CLogger</c>
	/// </param>
	/// <returns>
	///		Reference to <c>this</c> object
	///		to continue work with class methods in one line
	/// </returns>
	/// <example>
	///		const auto* testLogger = new CLogger("TestName", ELogLevel::DEBUG_LEVEL);
	///		testLogger->AddLogConfig(ELogConfig::MESSAGE)
	///			.AddLogConfig(ELogConfig::LINE_NUMBER)
	///			.AddLogConfig(ELogConfig::PARAMS)
	///			.AddLogConfig(ELogConfig::MESSAGE); // won't be added
	/// </example>
	CLogger& AddLogConfig(ELogConfig log_config);

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
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG_LEVEL);
	///		auto* testLogger = testBuilder->Build();
	///		testLogger->SetLogConfig(ELogConfig::MESSAGE, ELogConfig::LOG_LEVEL,
	///		ELogConfig::PARAMS);
	///		testLogger->PrintLogMessage(CLogMessage(/*...*/));
	/// </example>
	template<typename... Args>
	void PrintLogMessage(const CLogMessage<Args...>& log_message) const;

	/// <summary>
	///		Prints to all streams info about <c>CLogger</c>
	/// </summary>
	/// <example>
	///		const auto* testLogger = new CLogger("TestName", ELogLevel::DEBUG_LEVEL);
	///		testLogger->PrintLogInfo();
	/// </example>
	void PrintLogInfo() const;

	CLogger& operator=(const CLogger&) = delete;
	/// <summary>
	///		Default move assign operator for <c>CLogger</c>
	/// </summary>
	/// <param name="move">
	///		Rvalue reference to <c>CLogger</c>
	/// </param>
	/// <example>
	///		auto* testLogger1       = new CLogger("TestName", ELogLevel::DEBUG_LEVEL);
	///		const auto* testLogger2 = std::move(*testLogger1);
	/// </example>
	CLogger& operator=(CLogger&& move) noexcept;

private:
	ELogLevel m_log_level;
	ELogFlush m_log_flush;
	std::string m_log_name;
	std::list<ELogConfig> m_log_config_list;
	std::list<std::pair<std::reference_wrapper<std::ostream>,
		std::unique_ptr<std::mutex>>> m_write_stream_list;

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
	template<typename... Args>
	void PrintToAllStreams(const CLogMessage<Args...>& log_message) const;

	template<typename... Args>
	std::string MakeMessage(const CLogMessage<Args...>& log_message) const;
	
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
	std::ostream& PrintLogMessage(const std::string& message,
		std::ostream& stream) const;

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
	std::ostream& PrintParams(const CLogMessage<Args...>& log_message,
		std::ostream& stream) const;
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
	template<typename TupleType, size_t... Size>
	std::ostream& PrintParams(const TupleType& tuple,
		std::index_sequence<Size...>, std::ostream& stream) const;

	/// <summary>
	///		Prints to all streams some <c>std::string</c>
	/// </summary>
	/// <param name="info">
	///		String to print
	/// </param>
	void PrintToAllStreams(const std::string& info) const;

	std::ostream& PrintLogInfo(const std::string& info,
		std::ostream& stream) const;

	inline std::ostream& FlushFunction(std::ostream&) const;
};

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

template<typename ... Args>
void CLogger::PrintToAllStreams(const CLogMessage<Args...>& log_message) const
{
	const std::string message = MakeMessage(log_message);
	for (const auto& [stream, mutex] : m_write_stream_list)
	{
		auto unique_lock = nullptr == mutex ?
			std::unique_lock<std::mutex>() :
			std::unique_lock<std::mutex>(*mutex);

		PrintLogMessage(message, stream);
	}
}

template<typename... Args>
std::string CLogger::MakeMessage(const CLogMessage<Args...>& log_message) const
{
	std::stringstream stream;
	for (const auto& config : m_log_config_list)
	{
		switch (config)
		{
			// TODO remove repeat-code
		case ELogConfig::THREAD_ID:
		{
			stream << "Thread id:" << " " << "[" << log_message.GetThreadId()
				<< "]" << " ";
			break;
		}
		case ELogConfig::CALL_TIME:
		{
			stream << "Time:" << " " << "[" << log_message.GetTimeString()
				<< "]" << " ";
			break;
		}
		case ELogConfig::FUNCTION_NAME:
		{
			stream << "Function:" << " " << log_message.GetFunctionString()
				<< " ";
			break;
		}
		case ELogConfig::FILE_NAME:
		{
			stream << "File:" << " " << log_message.GetFileString()
				<< " ";
			break;
		}
		case ELogConfig::LINE_NUMBER:
		{
			stream << "Line number:" << " " << log_message.GetLineNumber()
				<< " ";
			break;
		}
		case ELogConfig::MESSAGE:
		{
			stream << "Message:" << " " << "\"" << log_message.GetMessageString()
				<< '\"' << " ";
			break;
		}
		case ELogConfig::LOG_LEVEL:
		{
			stream << "[" << LogLevelToString(log_message.GetLogLevel())
				<< "]" << " ";
			break;
		}
		case ELogConfig::PARAMS:
		{
			PrintParams(log_message, stream);
			break;
		}
		case ELogConfig::LOG_NAME:
		{
			stream << m_log_name << " ";
			break;
		}
		case ELogConfig::NONE:
		{
			break;
		}
		}

		FlushFunction(stream);
	}

	// TODO remove last char " "
	return stream.str();
}

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

template<typename TupleType, size_t ...Size>
std::ostream& CLogger::PrintParams(const TupleType& tuple,
	std::index_sequence<Size...> index, std::ostream& stream) const
{
	(..., (stream << (0u == Size ? "" : ", ") << std::get<Size>(tuple).first << " "
		<< "=" << " " << std::get<Size>(tuple).second));

	return stream;
}

inline std::ostream& CLogger::FlushFunction(std::ostream& stream) const {
	switch (m_log_flush)
	{
	case ELogFlush::FLUSH:
	{
		return stream << std::flush;
	}
	case ELogFlush::NOT_FLUSH:
	{
		return stream;
	}
	default:
	{
		return stream;
	}
	}
}
