#pragma once

#include"../../CFile/CFile.h"
#include "../Interfaces/IReader.h"

class CLegacyIn : public IReader
{
public:
	CLegacyIn() = delete;
	explicit CLegacyIn(CFile& in);
	CLegacyIn(const CLegacyIn& copy) = delete;
	CLegacyIn(CLegacyIn&&) noexcept;

	~CLegacyIn() override;

	bool Read(char& value) override;
	bool Read(std::string& value) override;

	bool ReadLine(std::string& value) override;
private:
	std::reference_wrapper<CFile> in_;

	template<typename Type>
	bool Read(const char* format, Type& value);
};

inline CLegacyIn::CLegacyIn(CFile& in) : in_(in)
{}

inline CLegacyIn::CLegacyIn(CLegacyIn&&) noexcept = default;
inline CLegacyIn::~CLegacyIn() = default;

inline bool CLegacyIn::Read(char& value)
{
	return Read<char>("%c", value);
}

inline bool CLegacyIn::Read(std::string& value)
{
	constexpr auto size = 1024u;
	char buffer[size] = "";
	const auto result = Read<char[size]>("%s", buffer);
	value = buffer;
	return result;
}

inline bool CLegacyIn::ReadLine(std::string& value)
{
	constexpr auto size = 1024u;
	char buffer[size] = "";
	if (nullptr == fgets(buffer, size, in_.get()))
	{
		return false;
	}
	
	value = buffer;
	value.erase(std::remove(value.begin(), value.end(), '\n'), value.end());
	
	return true;
}

template<typename Type>
bool CLegacyIn::Read(const char* const format, Type& value)
{
	return fscanf(in_.get(), format, &value) ? true : false;
}

inline CFile lStdIn(stdin);
inline CLegacyIn LCin(lStdIn);
