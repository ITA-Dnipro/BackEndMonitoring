#include "stdafx.h"

#include "CLogBuilder/CLogBuilder.h"

CLogBuilder::CLogBuilder(const std::string& log_name, const ELogLevel log_level)
	: CLogBuilder(log_name, log_level, ELogFlush::FLUSH)
{}

CLogBuilder::CLogBuilder(const std::string& log_name, const ELogLevel log_level,
	const ELogFlush log_flush)
	: m_log_level(log_level), m_log_flush(log_flush),
	  m_log_name(log_name),
	  m_log_buffer({ CLogMessage<>(typeid(*this).name() + std::string(" ") + "was created",
	  m_buffer_log_level, __LINE__, LogUtils::GetFileNameByPath(__FILE__),
		__FUNCTION__, LogUtils::GetTime(), LogUtils::GetThisThreadIdString()) })
{}

CLogBuilder::CLogBuilder(CLogBuilder&& move) = default;

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
	m_log_buffer.push
		(CLogMessage<>(std::string("Log level") +
			" " + LogLevelToString(log_level) + " " + "was set",
			m_buffer_log_level, __LINE__, LogUtils::GetFileNameByPath(__FILE__),
			__FUNCTION__, LogUtils::GetTime(), LogUtils::GetThisThreadIdString()));

	return *this;
}

CLogBuilder& CLogBuilder::SetLogName(const std::string& log_name)
{
	if (log_name != m_log_name)
	{
		m_log_name = log_name;
	}
	m_log_buffer.push
	(CLogMessage<>(std::string("Log name") + " " + "was set",
		m_buffer_log_level, __LINE__, LogUtils::GetFileNameByPath(__FILE__),
		__FUNCTION__, LogUtils::GetTime(), LogUtils::GetThisThreadIdString()));

	return *this;
}

ELogFlush CLogBuilder::GetLogFlush() const
{
	return m_log_flush;
}

CLogBuilder& CLogBuilder::SetLogFlush(const ELogFlush log_flush)
{
	if (m_log_flush != log_flush)
	{
		m_log_flush = log_flush;
	}
	m_log_buffer.push
		(CLogMessage<>(std::string("Log flush") +
		" " + LogFlushToString(log_flush) + " " + "was set",
		m_buffer_log_level, __LINE__, LogUtils::GetFileNameByPath(__FILE__),
		__FUNCTION__, LogUtils::GetTime(), LogUtils::GetThisThreadIdString()));
	
	return *this;
}

CLogBuilder& CLogBuilder::AddThreadSafeStream(std::ostream& stream)
{
	m_write_stream_safe_list.emplace_front(stream);
	m_log_buffer.push
	(CLogMessage<>(std::string("Thread safe stream was added"),
		m_buffer_log_level, __LINE__, LogUtils::GetFileNameByPath(__FILE__),
		__FUNCTION__, LogUtils::GetTime(), LogUtils::GetThisThreadIdString()));
	
	return *this;
}

CLogBuilder& CLogBuilder::AddThreadUnsafeStream(std::ostream& stream)
{
	m_write_stream_unsafe_list.emplace_front(stream);
	m_log_buffer.push
		(CLogMessage<>(std::string("Thread unsafe stream was added"),
			m_buffer_log_level, __LINE__, LogUtils::GetFileNameByPath(__FILE__),
			__FUNCTION__, LogUtils::GetTime(), LogUtils::GetThisThreadIdString()));
	
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
	m_log_buffer.push
		(CLogMessage<>(std::string("Log config") +
		" " + LogConfigToString(log_config) + " " + "was added",
		m_buffer_log_level, __LINE__, LogUtils::GetFileNameByPath(__FILE__),
		__FUNCTION__, LogUtils::GetTime(), LogUtils::GetThisThreadIdString()));

	return *this;
}

CLogger* CLogBuilder::BuildLog()
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
	m_log_buffer.push
	(CLogMessage<>(std::string("Logger was built"),
		m_buffer_log_level, __LINE__, LogUtils::GetFileNameByPath(__FILE__),
		__FUNCTION__, LogUtils::GetTime(), LogUtils::GetThisThreadIdString()));

	PrintBuffer(log);
	
	return log;
}

std::unique_ptr<CLogger> CLogBuilder::BuildUniqueLog()
{
	return std::unique_ptr<CLogger>(BuildLog());
}

std::shared_ptr<CLogger> CLogBuilder::BuildSharedLog()
{
	return std::shared_ptr<CLogger>(BuildLog());
}

void CLogBuilder::PrintBuffer(CLogger* logger)
{
	while (!m_log_buffer.empty())
	{
		logger->PrintLogMessage(m_log_buffer.front());
		m_log_buffer.pop();
	}
}

CLogBuilder& CLogBuilder::operator=(CLogBuilder&& move) noexcept = default;
