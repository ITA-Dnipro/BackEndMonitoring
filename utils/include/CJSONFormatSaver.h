#pragma once

#include "json.hpp"

#include "CJSONFormatter.h"

class CJSONFormatSaver
{
public:
	CJSONFormatSaver() = delete;
	CJSONFormatSaver(const std::string& path_to_file) :
		m_path_to_file(path_to_file), m_number_of_spaces(3)
	{ };
	CJSONFormatSaver(const CJSONFormatSaver&) = delete;
	CJSONFormatSaver(const CJSONFormatSaver&&) = delete;
	
	[[nodiscard]] bool TrySaveToFile(CJSONFormatter& formatted_data);

private:
	std::string m_path_to_file;
	const unsigned short m_number_of_spaces;
};

