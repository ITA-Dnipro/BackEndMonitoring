#pragma once
#include "IPathConstructor.h"

class CDateTimePathConstructor : public IPathConstructor
{
public:
	CDateTimePathConstructor() = delete;
	CDateTimePathConstructor(const std::string& general_folder);
	CDateTimePathConstructor(const CDateTimePathConstructor&) = delete;
	CDateTimePathConstructor(CDateTimePathConstructor&&) = delete;

	virtual bool UpdatePathToFile(std::string& path) override;
	
private:
	bool IsCreatedGeneralFolder() const;
	char DetermineSectDividingSymbol(const std::string& path);

private:
	bool m_is_created_general_folder;
	const std::string m_general_folder;
	const size_t m_length_of_part = 2;
	std::string m_updated_path;
	std::string m_day;
	std::string m_hour;
	std::string m_extension;
};

