#pragma once
#include "stdafx.h"

#include <memory>
#include <list>

#include "ELogConfig/ELogConfig.h"
#include "CLogger/CLogger.h"
#include "ELogLevel/ELogLevel.h"

/// <summary>
///		Namespace, that contains all classes and functions
///		to work with CLogger and its macro-functions
/// </summary>
namespace Log
{
	/// <summary>
	///		Class, that sets basic configuration of <c>CLogger</c> and creates it
	/// </summary>
	class CLOGGER_API CLogBuilder {
	public:
		CLogBuilder() = delete;
		CLogBuilder(const std::string& log_name, ELogLevel log_level);
		CLogBuilder(const CLogBuilder& copy) = delete;
		CLogBuilder(CLogBuilder&& move) noexcept;

		~CLogBuilder() noexcept;

		[[nodiscard]] ELogLevel GetLogLevel() const;
		CLogBuilder& SetLogLevel(ELogLevel log_level);

		CLogBuilder& AddThreadSafeStream(std::ostream& stream);
		CLogBuilder& AddThreadUnsafeStream(std::ostream& stream);

		template<typename... Args>
		CLogBuilder& SetLogConfig(Args... args);

		[[nodiscard]] std::string GetLogName() const;
		CLogBuilder& SetLogName(const std::string& log_name);

		[[nodiscard]] CLogger* BuildLog() const;
		[[nodiscard]] std::unique_ptr<CLogger> BuildUniqueLog() const;
		[[nodiscard]] std::shared_ptr<CLogger> BuildSharedLog() const;

		CLogBuilder& operator=(const CLogBuilder&) = delete;
		CLogBuilder& operator=(CLogBuilder&&) noexcept;

	private:
		ELogLevel m_log_level;
		std::string m_log_name;
		std::list<ELogConfig> m_log_config_list;
		std::list<std::reference_wrapper<std::ostream>> m_write_stream_safe_list;
		std::list<std::reference_wrapper<std::ostream>> m_write_stream_unsafe_list;

		CLogBuilder& AddLogConfig(ELogConfig log_config);
		template<typename... Args>
		CLogBuilder& AddLogConfig(ELogConfig logConfig, Args... args);
	};

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
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG);
	///		testBuilder->SetLogConfig(ELogConfig::MESSAGE, ELogConfig::LINE_NUMBER,
	///		ELogConfig::PARAMS, ELogConfig::LINE_NUMBER /* won't be added */);
	/// </example>
	template<typename... Args>
	CLogBuilder& CLogBuilder::SetLogConfig(Args... args) {
		this->m_log_config_list.clear();
		this->AddLogConfig(args...);
		return *this;
	}

	template<typename... Args>
	CLogBuilder& CLogBuilder::AddLogConfig(const ELogConfig logConfig, Args... args) {
		this->m_log_config_list.emplace_back(logConfig);
		return this->AddLogConfig(args...);
	}
}
