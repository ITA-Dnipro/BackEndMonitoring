#pragma once
#include "stdafx.h"

#include "ELogConfig/ELogConfig.h"
#include "ELogLevel/ELogLevel.h"
#include "ELogFlush/ELogFlush.h"
#include "CLogger/CLogger.h"
#include "Utils/Utils.h"

/// <summary>
///		Class, that sets basic configuration of <c>CLogger</c> and creates it
/// </summary>
class CLOGGER_API CLogBuilder
{
public:
	CLogBuilder() = delete;
	/// <summary>
	///		Explicit two-parameter ctor, that initializes
	///		name and <c>ELogLevel</c> of future <c>CLogger</c>
	/// </summary>
	/// <param name="log_name">
	///		Unique name of future <c>CLogger</c> instance</param>
	///	<param name="log_level">
	///		<c>ELogLevel</c> of future <c>CLogger</c>,
	///		which helps to filter out some messages
	/// </param>
	/// <example>
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG_LEVEL));
	/// </example>
	explicit CLogBuilder(const std::string& log_name, ELogLevel log_level);
	explicit CLogBuilder(const std::string& log_name, ELogLevel log_level, ELogFlush log_flush);
	CLogBuilder(const CLogBuilder& copy) = delete;
	/// <summary>
	///		Default move ctor for <c>CLogBuilder</c>
	/// </summary>
	/// <param name="move">
	///		Rvalue reference to <c>CLogBuilder</c>
	/// </param>
	/// <example>
	///		auto* testBuilder1       = new CLogBuilder("TestName", ELogLevel::DEBUG_LEVEL);
	///		const auto* testBuilder2 = new CLogBuilder(std::move(*testBuilder1));
	/// </example>
	CLogBuilder(CLogBuilder&& move) noexcept = default;

	/// <summary>
	///		Default dtor of <c>CLogBuilder</c>
	/// </summary>
	~CLogBuilder() noexcept;

	/// <summary>
	///		<c>ELogLevel</c> of future <c>CLogger</c> getter
	/// </summary>
	/// <returns>
	///		<c>ELogLevel</c>, which helps to filter out some messages
	/// </returns>
	/// <example>
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG_LEVEL);
	///		ELogLevel test = testBuilder->GetLogLevel();
	/// </example>
	[[nodiscard]] ELogLevel GetLogLevel() const;
	/// <summary>
	///		<c>ELogLevel</c> of future <c>CLogger</c> setter
	/// </summary>
	/// <param name="log_level">
	///		<c>ELogLevel</c> to set
	///	</param>
	/// <returns>
	///		Reference to <c>this</c> object
	///		to continue work with class methods in one line
	/// </returns>
	/// <example>
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG_LEVEL);
	///		testBuilder->SetLogLevel(ELogLevel::TRACE_LEVEL);
	/// </example>
	CLogBuilder& SetLogLevel(ELogLevel log_level);

	/// <summary>
	///		Clears all <c>ELogConfig</c> that was stored at <c>CLogBuilder</c>
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
	///		testBuilder->SetLogConfig(ELogConfig::MESSAGE, ELogConfig::LINE_NUMBER,
	///		ELogConfig::PARAMS, ELogConfig::LINE_NUMBER /* won't be added */);
	/// </example>
	template<typename... Args>
	CLogBuilder& SetLogConfig(Args... args);

	/// <summary>
	///		Name of future <c>CLogger</c> getter
	/// </summary>
	/// <returns>
	///		Unique name of future <c>CLogger</c>
	/// </returns>
	/// <example>
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG_LEVEL);
	///		std::string name = testBuilder->GetLogName();
	/// </example>
	[[nodiscard]] std::string GetLogName() const;
	/// <summary>
	///		Name of future <c>CLogger</c> setter
	/// </summary>
	/// <param name="log_name">
	///		<c>std::string</c> to set
	///	</param>
	/// <returns>
	///		Reference to <c>this</c> object
	///		to continue work with class methods in one line
	/// </returns>
	/// <example>
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG_LEVEL);
	///		testBuilder->SetLogName(std::string("new_name"));
	/// </example>
	CLogBuilder& SetLogName(const std::string& log_name);

	/// <summary>
	///		<c>ELogFlush</c> getter
	/// </summary>
	/// <returns>
	///		<c>ELogFlush</c>, which indicates if output stream flushes
	/// </returns>
	/// <example>
	///		const auto* testLoggerBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG_LEVEL,
	///			ELogFlush::FLUSH);
	///		ELogFlush test = testLoggerBuilder->GetLogFlush();
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
	///		const auto* testLoggerBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG_LEVEL,
	///			ELogFlush::FLUSH);
	///		testLoggerBuilder->SetLogFlush(ELogLevel::NOT_FLUSH);
	/// </example>
	CLogBuilder& SetLogFlush(ELogFlush log_flush);
	
	/// <summary>
	///		Adds thread safe (with <c>std::mutex</c>) output stream of future <c>CLogger</c>.
	///		Neither <c>CLogger</c> nor the <c>CLogBuilder</c> owns the stream,
	///		so they won't call there dtors
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
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG_LEVEL);
	///		testBuilder->AddThreadSafeStream(std::cout)
	///			.AddThreadSafeStream(std::cerr)
	///			.AddThreadSafeStream(testFile);	
	/// </example>
	CLogBuilder& AddThreadSafeStream(std::ostream& stream);
	/// <summary>
	///		Adds thread unsafe (without <c>std::mutex</c>) output
	///		stream of future <c>CLogger</c>. Neither <c>CLogger</c>
	///		nor the <c>CLogBuilder</c> owns the stream, so they
	///		won't call there dtors
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
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG_LEVEL);
	///		testBuilder->AddThreadUnsafeStream(std::cout)
	///			.AddThreadUnsafeStream(std::cerr)
	///			.AddThreadUnsafeStream(testFile);	
	/// </example>
	CLogBuilder& AddThreadUnsafeStream(std::ostream& stream);

	template<typename... Args>
	CLogBuilder& AddLogConfig(ELogConfig log_config, Args... args);
	CLogBuilder& AddLogConfig(ELogConfig log_config);

	/// <summary>
	///		Allocates memory and creates <c>CLogger</c>
	/// </summary>
	/// <returns>
	///		C-pointer to <c>CLogger</c> object, that have initialized
	///		by the values, that contains <c>CLogBuilder</c> object
	/// </returns>
	/// <example>
	///		const auto* testBuilder  = new CLogBuilder("TestName", ELogLevel::DEBUG_LEVEL);
	///		const CLogger* testLogger = testBuilder->BuildLog();
	/// </example>
	[[nodiscard]] CLogger* BuildLog();
	/// <summary>
	///		Allocates memory and creates <c>CLogger</c>
	/// </summary>
	/// <returns>
	///		Unique pointer to <c>CLogger</c> object, that have initialized
	///		by the values, that contains <c>CLogBuilder</c> object
	/// </returns>
	/// <example>
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG_LEVEL);
	///		const std::unique_ptr<CLogger> testLogger = testBuilder->BuildUniqueLog();
	/// </example>
	[[nodiscard]] std::unique_ptr<CLogger> BuildUniqueLog();
	/// <summary>
	///		Allocates memory and creates <c>CLogger</c>
	/// </summary>
	/// <returns>
	///		Shared pointer to <c>CLogger</c> object, that have initialized
	///		by the values, that contains <c>CLogBuilder</c> object
	/// </returns>
	/// <example>
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG_LEVEL);
	///		const std::unique_ptr<CLogger> testLogger = testBuilder->BuildSharedLog();
	/// </example>
	[[nodiscard]] std::shared_ptr<CLogger> BuildSharedLog();

	CLogBuilder& operator=(const CLogBuilder&) = delete;
	/// <summary>
	///		Default move assign operator for <c>CLogBuilder</c>
	/// </summary>
	/// <param name="move">
	///		Rvalue reference to <c>CLogBuilder</c>
	/// </param>
	/// <example>
	///		auto* testBuilder1       = new CLogBuilder("TestName", ELogLevel::DEBUG_LEVEL);
	///		const auto* testBuilder2 = std::move(*testBuilder1);
	/// </example>
	CLogBuilder& operator=(CLogBuilder&&) noexcept;

private:
	static ELogLevel m_buffer_log_level;
	
	ELogLevel m_log_level;
	ELogFlush m_log_flush;
	std::string m_log_name;
	std::queue<CLogMessage<>> m_log_buffer;
	std::list<ELogConfig> m_log_config_list;
	
	std::list<std::reference_wrapper<std::ostream>> m_write_stream_safe_list;
	std::list<std::reference_wrapper<std::ostream>> m_write_stream_unsafe_list;

	void PrintBuffer(CLogger* logger);
};

inline ELogLevel CLogBuilder::m_buffer_log_level = ELogLevel::PROD_LEVEL;

template<typename... Args>
CLogBuilder& CLogBuilder::SetLogConfig(Args... args)
{
	m_log_config_list.clear();
	AddLogConfig(args...);
	m_log_buffer.push(CLogMessage<>(std::string("Configs was set"),
		m_buffer_log_level, __LINE__, LogUtils::GetFileNameByPath(__FILE__),
		__FUNCTION__, LogUtils::GetTime(), LogUtils::GetThisThreadIdString()));
	
	return *this;
}

template<typename... Args>
CLogBuilder& CLogBuilder::AddLogConfig(const ELogConfig log_config, Args... args)
{
	if (std::find(m_log_config_list.begin(),
		m_log_config_list.end(), log_config) == m_log_config_list.end())
	{
		m_log_config_list.emplace_back(log_config);
	}
	m_log_buffer.push(CLogMessage<>(std::string("Config") +
		" " + LogConfigToString(log_config) + " " + "was added",
		m_buffer_log_level, __LINE__, LogUtils::GetFileNameByPath(__FILE__),
		__FUNCTION__, LogUtils::GetTime(), LogUtils::GetThisThreadIdString()));

	
	return AddLogConfig(args...);
}