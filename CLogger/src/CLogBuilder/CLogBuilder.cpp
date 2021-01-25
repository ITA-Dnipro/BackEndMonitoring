#include "stdafx.h"

#include "CLogBuilder/CLogBuilder.h"

CLogBuilder::CLogBuilder(const std::string& log_name, const ELogLevel log_level)
	: m_log_level(log_level), m_log_name(log_name)
{}

CLogBuilder::CLogBuilder(CLogBuilder&& move) noexcept = default;

CLogBuilder::~CLogBuilder() noexcept = default;

ELogLevel CLogBuilder::GetLogLevel() const
{
	return m_log_level;
}

std::string CLogBuilder::GetLogName() const
{
	return m_log_name;
}

CLogBuilder& CLogBuilder::SetLogLevel(const ELogLevel log_level)
{
	if (log_level != m_log_level)
	{
		m_log_level = log_level;
	}

	return *this;
}

CLogBuilder& CLogBuilder::SetLogName(const std::string& log_name)
{
	if (log_name != m_log_name)
	{
		m_log_name = log_name;
	}

	return *this;
}

CLogBuilder& CLogBuilder::AddThreadSafeStream(std::ostream& stream)
{
	m_write_stream_safe_list.emplace_front(stream);
	return *this;
}

CLogBuilder& CLogBuilder::AddThreadUnsafeStream(std::ostream& stream)
{
	m_write_stream_unsafe_list.emplace_front(stream);
	return *this;
}

/// <summary>
///		Adds a single <c>ELogConfig</c> of future <c>CLogger</c> setter.
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
///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG_LEVEL);
///		testBuilder->AddLogConfig(ELogConfig::MESSAGE)
///			.AddLogConfig(ELogConfig::LINE_NUMBER)
///			.AddLogConfig(ELogConfig::PARAMS)
///			.AddLogConfig(ELogConfig::MESSAGE); // won't be added
/// </example>
CLogBuilder& CLogBuilder::AddLogConfig(const ELogConfig log_config)
{
	if (std::find(m_log_config_list.begin(),
		m_log_config_list.end(), log_config) == m_log_config_list.end())
	{
		m_log_config_list.emplace_back(log_config);
	}

	return *this;
}

CLogger* CLogBuilder::BuildLog() const
{
	auto* log = new CLogger(m_log_name, m_log_level);

	for (const auto& config : m_log_config_list)
	{
		log->AddLogConfig(config);
	}

	for (const auto& stream : m_write_stream_safe_list)
	{
		log->AddThreadSafeStream(stream);
	}

	for (const auto& stream : m_write_stream_unsafe_list)
	{
		log->AddThreadUnsafeStream(stream);
	}

	return log;
}

std::unique_ptr<CLogger> CLogBuilder::BuildUniqueLog() const
{
	return std::unique_ptr<CLogger>(BuildLog());
}

std::shared_ptr<CLogger> CLogBuilder::BuildSharedLog() const
{
	return std::shared_ptr<CLogger>(BuildLog());
}

CLogBuilder& CLogBuilder::operator=(CLogBuilder&& move) noexcept = default;
