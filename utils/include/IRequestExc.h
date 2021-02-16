#pragma once

enum class ERequestRangeSpecification;

class IRequestExc
{
public:
	IRequestExc() = delete;
	IRequestExc(const std::string& request);
	IRequestExc(const IRequestExc&) = delete;
	IRequestExc(IRequestExc&&);
	virtual bool Execute(std::string& answer) = 0;

private:
	//change
	[[nodiscard]] bool DetermineDateRange();
	[[nodiscard]] ERequestRangeSpecification IsSpecial();

private:
	const std::string& m_request;
	std::string m_range_of_data;
	ERequestRangeSpecification m_range_specification;
};

