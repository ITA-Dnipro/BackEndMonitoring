#pragma once

#include"../../CFile/CFile.h"
#include "../Interfaces/IReader.h"

class CLegacyIn : public IReader
{
public:
	CLegacyIn();
	explicit CLegacyIn(const CFile& in);
	CLegacyIn(const CLegacyIn& copy) = delete;
	CLegacyIn(CLegacyIn&&) noexcept;

	~CLegacyIn() override;

	bool Read(char& value) override;
	bool Read(std::string& value) override;

	bool ReadLine(std::string& value) override;
private:
	CFile in_;

	template<typename Type>
	bool Read(const char* format, Type& value);
};

inline CLegacyIn::CLegacyIn() : CLegacyIn(CFile(stdin))
{}

inline CLegacyIn::CLegacyIn(const CFile& in) : in_(in)
{}

inline CLegacyIn::CLegacyIn(CLegacyIn&&) noexcept = default;
inline CLegacyIn::~CLegacyIn() = default;

inline bool CLegacyIn::Read(char& value)
{
	return Read<char>("%c", value);
}

inline bool CLegacyIn::Read(std::string& value)
{
	return Read<std::string>("%s", value);
}

inline bool CLegacyIn::ReadLine(std::string& value)
{
	constexpr auto size = 1024u;
	char buffer[size] = "";
	if (nullptr == fgets(buffer, size, in_))
	{
		return false;
	}
	
	value = buffer;
	return true;
}

template<typename Type>
bool CLegacyIn::Read(const char* const format, Type& value)
{
	return fscanf(in_, format, &value) ? true : false;
}

inline CLegacyIn LCin;
