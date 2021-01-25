#pragma once

class CJSONFormatter;

class CJSONFormatSaver
{
public:
	CJSONFormatSaver() = delete;
	CJSONFormatSaver(const std::string& path_to_file);
	CJSONFormatSaver(const CJSONFormatSaver&) = delete;
	CJSONFormatSaver(const CJSONFormatSaver&&) = delete;
	
	[[nodiscard]] bool TrySaveToFile(CJSONFormatter& formatted_data);

protected:
	[[nodiscard]] bool TryWriteToFile(std::ofstream& JSON_file_to_save, CJSONFormatter& formatted_data);

private:
	std::string m_path_to_file;
	const unsigned short m_number_of_spaces;
};

