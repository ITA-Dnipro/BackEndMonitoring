#pragma once

class IFindFileByValue
{
public:
	virtual bool TryFindFileByValue(const std::string& value,
		const std::string& path_to_general_folder, std::string& path_to_file) 
		= 0;

protected:
	bool TryFindFileByValueInFolder(const std::string& value,
		const std::string& path_to_general_folder, std::string& path_to_file);
};

