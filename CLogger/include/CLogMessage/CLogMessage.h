#pragma once
#include "stdafx.h"

#include "ELogLevel/ELogLevel.h"

template<typename... Args>
class CLogMessage
{
public:
	CLogMessage() = delete;
	explicit CLogMessage(const std::string& messageString, ELogLevel logLevel,
		unsigned lineNumber, const std::string& fileString,
		const std::string& functionString,
		const std::string& timeString, const std::string& threadId);

	explicit CLogMessage(const std::string& messageString, ELogLevel logLevel,
		unsigned lineNumber, const std::string& fileString,
		const std::string& functionString, const std::string& timeString,
		const std::string& threadId,
		const std::tuple<std::pair<const char*, Args>...>& args);

	CLogMessage(const CLogMessage&);
	CLogMessage(CLogMessage&&) noexcept;

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
	return this->m_log_level;
}

template<typename... Args>
unsigned CLogMessage<Args...>::GetLineNumber() const
{
	return this->m_line_number;
}

template<typename... Args>
std::string CLogMessage<Args...>::GetThreadId() const
{
	return this->m_thread_id;
}

template<typename... Args>
std::string CLogMessage<Args...>::GetFileString() const
{
	return this->m_file_string;
}

template<typename... Args>
std::string CLogMessage<Args...>::GetFunctionString() const
{
	return this->m_function_string;
}

template<typename... Args>
std::string CLogMessage<Args...>::GetTimeString() const
{
	return this->m_time_string;
}

template<typename... Args>
std::string CLogMessage<Args...>::GetMessageString() const
{
	return this->m_message_string;
}

template<typename... Args>
std::tuple<std::pair<const char*, Args>...> CLogMessage<Args...>::GetParams() const
{
	return this->m_param_tuple;
}

template<typename... Args>
CLogMessage<Args...>& CLogMessage<Args...>::operator=(const CLogMessage&) = default;
template<typename... Args>
CLogMessage<Args...>& CLogMessage<Args...>::operator=(CLogMessage&&) noexcept = default;
