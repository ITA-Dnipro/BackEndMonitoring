#pragma once
#pragma warning( disable : 4251 )
#include "stdafx.h"

#include "ELogLevel/ELogLevel.h"

/// <summary>
///		Stores some message with different data
/// </summary>
template<typename... Args>
class CLogMessage
{
public:
	CLogMessage() = delete;
	/// <summary>
	///		Explicit multi-parameters ctor, that initializes
	///		<c>CLogMessage</c> without additional parameters
	/// </summary>
	/// <param name="messageString">
	///		Message to output <c>std::string</c>
	/// </param>
	/// <param name="logLevel">
	///		Logging level of message
	/// </param>
	/// <param name="lineNumber">
	///		Number of string where is the command
	/// </param>
	/// <param name="fileString">
	///		Name of file where is the command
	/// </param>
	/// <param name="functionString">
	///		Name of function where if the command
	/// </param>
	/// <param name="timeString">
	///		Time when command was called
	/// </param>
	/// <param name="threadId">
	///		Thread from where command was called
	/// </param>
	/// <example>
	///		const auto* cLogMessage = new CLogMessage
	///			("Test", ELogLevel::DEBUG_LEVEL, 1u, "File.cpp",
	///			"Function", __TIMESTAMP__, "0000");
	/// </example>
	explicit CLogMessage(const std::string& messageString, ELogLevel logLevel,
		unsigned lineNumber, const std::string& fileString,
		const std::string& functionString,
		const std::string& timeString, const std::string& threadId);
	/// <summary>
	///		Explicit multi-parameters ctor, that initializes
	///		<c>CLogMessage</c> with additional parameters
	/// </summary>
	/// <param name="messageString">
	///		Message to output <c>std::string</c>
	/// </param>
	/// <param name="logLevel">
	///		Logging level of message
	/// </param>
	/// <param name="lineNumber">
	///		Number of string where is the command
	/// </param>
	/// <param name="fileString">
	///		Name of file where is the command
	/// </param>
	/// <param name="functionString">
	///		Name of function where if the command
	/// </param>
	/// <param name="timeString">
	///		Time when command was called
	/// </param>
	/// <param name="threadId">
	///		Thread from where command was called
	/// </param>
	/// <param name="args">
	///		Additional parameters
	/// </param>
	/// <example>
	///		const auto* cLogMessage = new CLogMessage
	///			("Test", ELogLevel::DEBUG_LEVEL, 1u, "File.cpp",
	///			"Function", __TIMESTAMP__, "0000",
	///			std::make_tuple(std::make_pair("First", 1ull)));
	/// </example>
	explicit CLogMessage(const std::string& messageString, ELogLevel logLevel,
		unsigned lineNumber, const std::string& fileString,
		const std::string& functionString, const std::string& timeString,
		const std::string& threadId,
		const std::tuple<std::pair<const char*, Args>...>& args);

	/// <summary>
	///		Copy ctor
	/// </summary>
	CLogMessage(const CLogMessage& copy);
	/// <summary>
	///		Move ctor
	/// </summary>
	/// <param name="move">
	///		Rvalue reference
	/// </param>
	CLogMessage(CLogMessage&& move) noexcept;

	~CLogMessage() noexcept;
	
	[[nodiscard]] ELogLevel GetLogLevel() const;
	[[nodiscard]] unsigned GetLineNumber() const;
	[[nodiscard]] std::string GetThreadId() const;
	[[nodiscard]] std::string GetFileString() const;
	[[nodiscard]] std::string GetFunctionString() const;
	[[nodiscard]] std::string GetTimeString() const;
	[[nodiscard]] std::string GetMessageString() const;
	[[nodiscard]] std::tuple<std::pair<const char*, Args>...> GetParams() const;

	CLogMessage& operator=(const CLogMessage&);
	CLogMessage& operator=(CLogMessage&&) noexcept;

protected:
	ELogLevel m_log_level;
	unsigned m_line_number;
	std::string m_thread_id;
	std::string m_file_string;
	std::string m_function_string;
	std::string m_time_string;
	std::string m_message_string;
	std::tuple<std::pair<const char*, Args>...> m_param_tuple;
};

template<typename... Args>
CLogMessage<Args...>::CLogMessage(const std::string& messageString,
	const ELogLevel logLevel, const unsigned lineNumber,
	const std::string& fileString, const std::string& functionString,
	const std::string& timeString, const std::string& threadId)
	: CLogMessage(messageString, logLevel, lineNumber, fileString,
		functionString, timeString, threadId, {})
{}

template<typename... Args>
CLogMessage<Args...>::CLogMessage(const std::string& messageString, const ELogLevel logLevel,
	const unsigned lineNumber, const std::string& fileString,
	const std::string& functionString, const std::string& timeString,
	const std::string& threadId, const std::tuple<std::pair<const char*, Args>...>& args)
	: m_log_level(logLevel), m_line_number(lineNumber), m_thread_id(threadId),
	m_file_string(fileString), m_function_string(functionString),
	m_time_string(timeString), m_message_string(messageString),
	m_param_tuple(args)
{}

template<typename... Args>
CLogMessage<Args...>::CLogMessage(const CLogMessage&) = default;
template<typename... Args>
CLogMessage<Args...>::CLogMessage(CLogMessage&&) noexcept = default;

template<typename... Args>
CLogMessage<Args...>::~CLogMessage() noexcept = default;

template<typename... Args>
ELogLevel CLogMessage<Args...>::GetLogLevel() const
{
	return m_log_level;
}

template<typename... Args>
unsigned CLogMessage<Args...>::GetLineNumber() const
{
	return m_line_number;
}

template<typename... Args>
std::string CLogMessage<Args...>::GetThreadId() const
{
	return m_thread_id;
}

template<typename... Args>
std::string CLogMessage<Args...>::GetFileString() const
{
	return m_file_string;
}

template<typename... Args>
std::string CLogMessage<Args...>::GetFunctionString() const
{
	return m_function_string;
}

template<typename... Args>
std::string CLogMessage<Args...>::GetTimeString() const
{
	return m_time_string;
}

template<typename... Args>
std::string CLogMessage<Args...>::GetMessageString() const
{
	return m_message_string;
}

template<typename... Args>
std::tuple<std::pair<const char*, Args>...> CLogMessage<Args...>::GetParams() const
{
	return m_param_tuple;
}

template<typename... Args>
CLogMessage<Args...>& CLogMessage<Args...>::operator=(const CLogMessage&) = default;
template<typename... Args>
CLogMessage<Args...>& CLogMessage<Args...>::operator=(CLogMessage&&) noexcept = default;
