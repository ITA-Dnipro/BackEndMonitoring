#include "stdafx.h"

#include "CLogger/CLogger.h"

CLOGGER_API extern auto logger = std::unique_ptr<CLogger>(nullptr);

CLogger::CLogger(const std::string& log_name, const ELogLevel log_level)
	: m_log_level(log_level), m_log_name(log_name)
{}

CLogger::CLogger(CLogger&& move) noexcept = default;

CLogger::~CLogger() noexcept = default;

CLogger& CLogger::AddThreadSafeStream(std::ostream& stream)
{
	m_write_stream_list
		.emplace_back(stream, std::make_unique<std::mutex>());
	
	return *this;
}

CLogger& CLogger::AddThreadUnsafeStream(std::ostream& stream)
{
	m_write_stream_list
		.emplace_back(stream, std::unique_ptr<std::mutex>(nullptr));

	return *this;
}

ELogLevel CLogger::GetLogLevel() const
{
	return m_log_level;
}

CLogger& CLogger::SetLogLevel(const ELogLevel log_level)
{
	if (log_level != m_log_level)
	{
		m_log_level = log_level;
	}
	return *this;
}

std::string CLogger::GetLogName() const
{
	return m_log_name;
}

CLogger& CLogger::AddLogConfig(const ELogConfig log_config)
{
	if (std::find(m_log_config_list.begin(),
		m_log_config_list.end(), log_config) == m_log_config_list.end())
	{
		m_log_config_list.emplace_back(log_config);
	}
	
	return *this;
}

void CLogger::PrintLogInfo() const
{
	if (m_write_stream_list.empty()
		|| m_log_config_list.empty())
	{
		return;
	}
	
	std::stringstream ss;
	ss << "CLogger name:" << " " << "\"" << m_log_name << "\"" << " "
	   << "Level:" << " " << "[" << LogLevelToString(m_log_level)
	   << "]" << " ";

	if (!m_log_config_list.empty())
	{
		ss << "Output order:" << " "
		   << LogConfigToString(*m_log_config_list.begin()) << std::flush;

		for (auto config = ++m_log_config_list.cbegin();
			config != m_log_config_list.cend(); ++config)
		{
			ss << "," << " " << LogConfigToString(*config) << std::flush;
		}
	}
	
	PrintToAllStreams(ss.str());
}

void CLogger::PrintToAllStreams(const std::string& info) const {
	for (const auto& [stream, mutex] : m_write_stream_list)
	{
		auto unique_lock = nullptr == mutex ?
			std::unique_lock<std::mutex>() :
			std::unique_lock<std::mutex>(*mutex);
		
		PrintLogInfo(info, stream);
	}
}

CLogger& CLogger::operator=(CLogger&& move) noexcept = default;

std::ostream& CLogger::PrintLogInfo(const std::string& info, // TODO: maybe static
	std::ostream& stream) const
{
	return stream << info << std::endl;
}
