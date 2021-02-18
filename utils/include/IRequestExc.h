#pragma once

enum class ERequestRangeSpecification;

class IRequestExc
{
public:
	IRequestExc() = delete;
	IRequestExc(const std::string& request);
	IRequestExc(const IRequestExc&) = delete;
	IRequestExc(IRequestExc&&) = default;
	virtual bool Execute(std::string& answer) = 0;

protected:
	//change
	[[nodiscard]] bool DetermineDateRange(const nlohmann::json& request);
	[[nodiscard]] ERequestRangeSpecification IsSpecial(
		const nlohmann::json& request);

protected:
	const std::string& m_request;
	std::vector<std::string> m_range_of_data;
	ERequestRangeSpecification m_range_specification;
};

