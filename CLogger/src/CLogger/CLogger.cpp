#include "stdafx.h"

#include "CLogger/CLogger.h"

/// <summary>
///		Namespace, that contains all classes and functions
///		to work with CLogger and its macro-functions
/// </summary>
namespace Log
{
	/// <summary>
	///		Explicit two-parameter ctor, that initializes
	///		name and <c>ELogLevel</c> of <c>CLogger</c>
	/// </summary>
	/// <param name="logName">
	///		Unique name of <c>CLogger</c> instance</param>
	/// </param>
	/// <param name="logLevel">
	///		<c>ELogLevel</c> of <c>CLogger</c>,
	///		which helps to filter out some messages
	/// </param>
	/// <example>
	///		const auto* testLogger = new CLogger("TestName", ELogLevel::DEBUG));
	/// </example>
	CLogger::CLogger(const std::string& logName, const ELogLevel logLevel)
		: m_log_level(logLevel), m_log_name(logName)
	{}

	/// <summary>
	///		Default move ctor for <c>CLogBuilder</c>
	/// </summary>
	/// <param name="move">
	///		Rvalue reference to <c>CLogger</c>
	/// </param>
	/// <example>
	///		auto* testLogger1       = new CLogger("TestName", ELogLevel::DEBUG);
	///		const auto* testLogger2 = new CLogger(std::move(*testLogger1));
	/// </example>
	CLogger::CLogger(CLogger&& move) noexcept = default;

	/// <summary>
	///		Default dtor of <c>CLogger</c>
	/// </summary>
	CLogger::~CLogger() noexcept = default;

	/// <summary>
	///		Adds output stream of <c>CLogger</c>.
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
	///		auto* testLogger1 = new CLogger("TestName", ELogLevel::DEBUG);
	///		testLogger1->AddStream(std::cout).AddStream(testFile);
	/// </example>
	CLogger& CLogger::AddStream(std::ostream& stream)
	{
		this->m_write_stream_list.emplace_back(stream);
		return *this;
	}

	/// <summary>
	///		<c>ELogLevel</c> getter
	/// </summary>
	/// <returns>
	///		<c>ELogLevel</c>, which helps to filter out some messages
	/// </returns>
	/// <example>
	///		const auto* testLogger = new CLogger("TestName", ELogLevel::DEBUG);
	///		ELogLevel test = testLogger->GetLogLevel();
	/// </example>
	ELogLevel CLogger::GetLogLevel() const
	{
		return this->m_log_level;
	}

	/// <summary>
	///		<c>ELogLevel</c> setter
	/// </summary>
	/// <param name="logLevel">
	///		<c>ELogLevel</c> to set
	///	</param>
	/// <returns>
	///		Reference to <c>this</c> object
	///		to continue work with class methods in one line
	/// </returns>
	/// <example>
	///		const auto* testLogger = new CLogger("TestName", ELogLevel::DEBUG);
	///		testLogger->SetLogLevel(ELogLevel::TRACE);
	/// </example>
	CLogger& CLogger::SetLogLevel(const ELogLevel logLevel)
	{
		if (logLevel != this->m_log_level)
		{
			this->m_log_level = logLevel;
		}
		return *this;
	}

	/// <summary>
	///		Name of <c>CLogger</c> getter
	/// </summary>
	/// <returns>
	///		Unique name of <c>CLogger</c>
	/// </returns>
	/// <example>
	///		const auto* testLogger = new CLogger("TestName", ELogLevel::DEBUG);
	///		std::string name = testLogger->GetLogName();
	/// </example>
	std::string CLogger::GetLogName() const
	{
		return this->m_log_name;
	}

	/// <summary>
	///		Adds a single <c>ELogConfig</c> of <c>CLogger</c> setter.
	///		The order of addition is important for output string of
	///		<c>CLogger</c>. Also it ignores duplicates
	/// </summary>
	/// <param name="logConfig">
	///		<c>ELogConfig</c> that modifies output string of <c>CLogger</c>
	/// </param>
	/// <returns>
	///		Reference to <c>this</c> object
	///		to continue work with class methods in one line
	/// </returns>
	/// <example>
	///		const auto* testLogger = new CLogger("TestName", ELogLevel::DEBUG);
	///		testLogger->AddLogConfig(ELogConfig::MESSAGE)
	///			.AddLogConfig(ELogConfig::LINE_NUMBER)
	///			.AddLogConfig(ELogConfig::PARAMS)
	///			.AddLogConfig(ELogConfig::MESSAGE); // won't be added
	/// </example>
	CLogger& CLogger::AddLogConfig(const ELogConfig logConfig)
	{
		if (std::find(this->m_log_config_list.begin(),
			this->m_log_config_list.end(), logConfig) == this->m_log_config_list.end())
		{
			this->m_log_config_list.emplace_back(logConfig);
		}
		return *this;
	}

	/// <summary>
	///		Prints to all streams info about <c>CLogger</c>
	/// </summary>
	/// <example>
	///		const auto* testLogger = new CLogger("TestName", ELogLevel::DEBUG);
	///		testLogger->PrintLogInfo();
	/// </example>
	void CLogger::PrintLogInfo() const
	{
		std::stringstream ss;
		ss << "CLogger name:" << " " << "\"" << this->m_log_name << "\"" << " "
		   << "Level:" << " " << "[" << LogLevelToString(this->m_log_level)
		   << "]" << " ";

		if (!this->m_log_config_list.empty())
		{
			ss << std::endl << "Output order:" << " "
				<< LogConfigToString(*this->m_log_config_list.begin()) << std::flush;

			for (auto config = ++this->m_log_config_list.cbegin();
				config != this->m_log_config_list.cend(); ++config)
			{
				ss << "," << " " << LogConfigToString(*config) << std::flush;
			}
		}

		const auto string = ss.str();
		for (const auto& stream : this->m_write_stream_list)
		{
			this->PrintLogInfo(string, stream);
		}
	}

	/// <summary>
	///		Default move assign operator for <c>CLogger</c>
	/// </summary>
	/// <param name="move">
	///		Rvalue reference to <c>CLogger</c>
	/// </param>
	/// <example>
	///		auto* testLogger1       = new CLogger("TestName", ELogLevel::DEBUG);
	///		const auto* testLogger2 = std::move(*testLogger1);
	/// </example>
	CLogger& CLogger::operator=(CLogger&& move) noexcept = default;

	std::ostream& CLogger::PrintLogInfo(const std::string& info, // TODO: maybe static
		std::ostream& stream) const
	{
		return stream << info << std::endl;
	}
}
