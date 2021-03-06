#pragma once

class CJSONFormatter;

class CJSONFormatSaver
{
public:
	CJSONFormatSaver() = delete;
	explicit CJSONFormatSaver(const std::filesystem::path& path_to_file);
	CJSONFormatSaver(const CJSONFormatSaver&) = delete;
	CJSONFormatSaver(const CJSONFormatSaver&&) = delete;
	
	[[nodiscard]] bool TrySaveToFile(const CJSONFormatter& formatted_data) const;
	[[nodiscard]] bool TrySaveToFile(const CJSONFormatter& formatted_data,
					std::streampos& block_begin, std::streampos& block_end) const;

protected:
	[[nodiscard]] bool TryWriteToFile(std::ofstream& JSON_file_to_save, 
		const CJSONFormatter& formatted_data) const;

private:
	const std::filesystem::path& m_path_to_file;
	const unsigned short m_number_of_spaces;
	const unsigned short m_bytes_to_last_data;
};

