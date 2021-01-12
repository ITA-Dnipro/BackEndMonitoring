#pragma once

#include "stdafx.h"
#include "CJSONFormatter.h"

class CJSONFormatSaver
{
public:
	CJSONFormatSaver() = delete;
	CJSONFormatSaver(std::string path_to_file) :
		m_path_to_file_(path_to_file)
	{ };
	CJSONFormatSaver(CJSONFormatSaver&) = delete;
	CJSONFormatSaver(CJSONFormatSaver&&) = delete;
	
	bool TrySaveToFile(CJSONFormatter& formatted_data);

private:
	std::string m_path_to_file_;
	const unsigned short m_number_of_spaces_ = 3;
};

