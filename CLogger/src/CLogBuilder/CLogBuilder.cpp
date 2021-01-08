#include "stdafx.h"

#include "CLogBuilder/CLogBuilder.h"

/// <summary>
///		Namespace, that contains all classes and functions
///		to work with CLogger and its macro-functions
/// </summary>
namespace Log
{
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
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG));
	/// </example>
	CLogBuilder::CLogBuilder(const std::string& log_name, const ELogLevel log_level)
		: m_log_level(log_level), m_log_name(log_name)
	{}

	/// <summary>
	///		Default move ctor for <c>CLogBuilder</c>
	/// </summary>
	/// <param name="move">
	///		Rvalue reference to <c>CLogBuilder</c>
	/// </param>
	/// <example>
	///		auto* testBuilder1       = new CLogBuilder("TestName", ELogLevel::DEBUG);
	///		const auto* testBuilder2 = new CLogBuilder(std::move(*testBuilder1));
	/// </example>
	CLogBuilder::CLogBuilder(CLogBuilder&& move) noexcept = default;

	/// <summary>
	///		Default dtor of <c>CLogBuilder</c>
	/// </summary>
	CLogBuilder::~CLogBuilder() noexcept = default;

	/// <summary>
	///		<c>ELogLevel</c> of future <c>CLogger</c> getter
	/// </summary>
	/// <returns>
	///		<c>ELogLevel</c>, which helps to filter out some messages
	/// </returns>
	/// <example>
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG);
	///		ELogLevel test = testBuilder->GetLogLevel();
	/// </example>
	ELogLevel CLogBuilder::GetLogLevel() const
	{
		return this->m_log_level;
	}

	/// <summary>
	///		Name of future <c>CLogger</c> getter
	/// </summary>
	/// <returns>
	///		Unique name of future <c>CLogger</c>
	/// </returns>
	/// <example>
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG);
	///		std::string name = testBuilder->GetLogName();
	/// </example>
	std::string CLogBuilder::GetLogName() const
	{
		return this->m_log_name;
	}

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
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG);
	///		testBuilder->SetLogLevel(ELogLevel::TRACE);
	/// </example>
	CLogBuilder& CLogBuilder::SetLogLevel(const ELogLevel log_level)
	{
		if (log_level != this->m_log_level)
		{
			this->m_log_level = log_level;
		}

		return *this;
	}

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
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG);
	///		testBuilder->AddThreadSafeStream(std::cout)
	///			.AddThreadSafeStream(std::cerr)
	///			.AddThreadSafeStream(testFile);	
	/// </example>
	CLogBuilder& CLogBuilder::AddThreadSafeStream(std::ostream& stream)
	{
		this->m_write_stream_safe_list.emplace_front(stream);
		return *this;
	}

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
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG);
	///		testBuilder->AddThreadUnsafeStream(std::cout)
	///			.AddThreadUnsafeStream(std::cerr)
	///			.AddThreadUnsafeStream(testFile);	
	/// </example>
	CLogBuilder& CLogBuilder::AddThreadUnsafeStream(std::ostream& stream)
	{
		this->m_write_stream_unsafe_list.emplace_front(stream);
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
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG);
	///		testBuilder->AddLogConfig(ELogConfig::MESSAGE)
	///			.AddLogConfig(ELogConfig::LINE_NUMBER)
	///			.AddLogConfig(ELogConfig::PARAMS)
	///			.AddLogConfig(ELogConfig::MESSAGE); // won't be added
	/// </example>
	CLogBuilder& CLogBuilder::AddLogConfig(const ELogConfig log_config)
	{
		if (std::find(this->m_log_config_list.begin(),
			this->m_log_config_list.end(), log_config) == this->m_log_config_list.end())
		{
			this->m_log_config_list.emplace_back(log_config);
		}

		return *this;
	}

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
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG);
	///		testBuilder->SetLogName(std::string("new_name"));
	/// </example>
	CLogBuilder& CLogBuilder::SetLogName(const std::string& log_name)
	{
		if (log_name != this->m_log_name)
		{
			this->m_log_name = log_name;
		}

		return *this;
	}

	/// <summary>
	///		Allocates memory and creates <c>CLogger</c>
	/// </summary>
	/// <returns>
	///		C-pointer to <c>CLogger</c> object, that have initialized
	///		by the values, that contains <c>CLogBuilder</c> object
	/// </returns>
	/// <example>
	///		const auto* testBuilder  = new CLogBuilder("TestName", ELogLevel::DEBUG);
	///		const CLogger* testLogger = testBuilder->BuildLog();
	/// </example>
	CLogger* CLogBuilder::BuildLog() const {
		auto* log = new CLogger(this->m_log_name, this->m_log_level);

		for (const auto& config : this->m_log_config_list)
		{
			log->AddLogConfig(config);
		}

		for (const auto& stream : this->m_write_stream_safe_list)
		{
			log->AddThreadSafeStream(stream);
		}

		for (const auto& stream : this->m_write_stream_unsafe_list)
		{
			log->AddThreadUnsafeStream(stream);
		}

		return log;
	}

	/// <summary>
	///		Allocates memory and creates <c>CLogger</c>
	/// </summary>
	/// <returns>
	///		Unique pointer to <c>CLogger</c> object, that have initialized
	///		by the values, that contains <c>CLogBuilder</c> object
	/// </returns>
	/// <example>
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG);
	///		const std::unique_ptr<CLogger> testLogger = testBuilder->BuildUniqueLog();
	/// </example>
	std::unique_ptr<CLogger> CLogBuilder::BuildUniqueLog() const
	{
		return std::unique_ptr<CLogger>(this->BuildLog());
	}

	/// <summary>
	///		Allocates memory and creates <c>CLogger</c>
	/// </summary>
	/// <returns>
	///		Shared pointer to <c>CLogger</c> object, that have initialized
	///		by the values, that contains <c>CLogBuilder</c> object
	/// </returns>
	/// <example>
	///		const auto* testBuilder = new CLogBuilder("TestName", ELogLevel::DEBUG);
	///		const std::unique_ptr<CLogger> testLogger = testBuilder->BuildSharedLog();
	/// </example>
	std::shared_ptr<CLogger> CLogBuilder::BuildSharedLog() const
	{
		return std::shared_ptr<CLogger>(this->BuildLog());
	}

	/// <summary>
	///		Default move assign operator for <c>CLogBuilder</c>
	/// </summary>
	/// <param name="move">
	///		Rvalue reference to <c>CLogBuilder</c>
	/// </param>
	/// <example>
	///		auto* testBuilder1       = new CLogBuilder("TestName", ELogLevel::DEBUG);
	///		const auto* testBuilder2 = std::move(*testBuilder1);
	/// </example>
	CLogBuilder& CLogBuilder::operator=(CLogBuilder&& move) noexcept = default;
}
