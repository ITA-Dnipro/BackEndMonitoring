#pragma once

enum class ERequestRangeSpecification;
class CDataProvider;

class IRequestExc
{
public:
	IRequestExc() = delete;
	explicit IRequestExc(const std::string& request,
		std::shared_ptr<CDataProvider> data_base);
	IRequestExc(const IRequestExc&) = delete;
	IRequestExc(IRequestExc&&) = default;
	virtual bool Execute(std::string& answer) = 0;

protected:
	//change
	[[nodiscard]] bool TryDetermineDateRange(const nlohmann::json& request);
	[[nodiscard]] ERequestRangeSpecification IsSpecial(
		const nlohmann::json& request);

protected:
	std::shared_ptr<CDataProvider> m_p_data_base;
	// do I really need a vector here???
	std::vector<std::string> m_range_of_data;
	const std::string& m_request;
};

