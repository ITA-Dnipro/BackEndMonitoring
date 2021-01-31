#pragma once

class CJSONFormatter;

class CJSONFormatSaver
{
public:
	CJSONFormatSaver() = delete;
	explicit CJSONFormatSaver(const std::string& path_to_file);
	CJSONFormatSaver(const CJSONFormatSaver&) = delete;
	CJSONFormatSaver(const CJSONFormatSaver&&) = delete;
	
	[[nodiscard]] bool TrySaveToFile(const CJSONFormatter& formatted_data) const;

protected:
	[[nodiscard]] bool TryWriteToFile(std::ofstream& JSON_file_to_save, 
		const CJSONFormatter& formatted_data) const;

private:
	const std::string m_path_to_file;
	const unsigned short m_number_of_spaces;
	const unsigned short m_num_of_bities_to_last_data;
};

