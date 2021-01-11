#pragma once

#include "stdafx.h"
#include "JSONFormatter.h"

class JSONFormatSaver
{
public:
	JSONFormatSaver() = delete;
	JSONFormatSaver(std::string path_to_file) :
		path_to_save_file_(path_to_file)
	{ };
	JSONFormatSaver(JSONFormatSaver&) = delete;
	JSONFormatSaver(JSONFormatSaver&&) = delete;
	
	bool TrySaveToFile(JSONFormatter& formatted_data);

private:
	std::string path_to_save_file_;
	const unsigned short number_of_spaces_ = 3;
};

