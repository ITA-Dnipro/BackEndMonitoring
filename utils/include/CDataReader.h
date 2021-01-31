#pragma once

class CDataReader
{
public:
	CDataReader() = default;
	CDataReader(CDataReader&) = delete;
	CDataReader(CDataReader&&) = delete;
	virtual	~CDataReader() = default;

	virtual bool Initialize(const std::string&) = 0;
	virtual bool IsFileInitialized() const = 0;
	virtual bool TryToGetStringData(const std::string& data_path, std::string& return_data) const = 0;

	static bool TryToConvertToBool(const std::string& data_to_convert, bool& return_data);
	static bool TryToConvertToInteger(const std::string& data_to_convert, int& return_data);
private:

};
