#pragma once

#include "../Interfaces/IWriter.h"
#include"../../CFile/CFile.h"

class CLegacyOut : public IWriter
{
public:
	CLegacyOut();
	explicit CLegacyOut(const CFile& out);
	CLegacyOut(const CLegacyOut& copy) = delete;
	CLegacyOut(CLegacyOut&& move) noexcept;

	CLegacyOut& operator=(const CLegacyOut& copy) = delete;
	CLegacyOut& operator=(CLegacyOut&& move) noexcept;
	~CLegacyOut() override;
	
	bool Write(char value) override;
	bool Write(const std::string& value) override;
	
	bool WriteLine(char value) override;
	bool WriteLine(const std::string& value) override;
	
	bool BreakLine() override;

private:
	CFile out_;

	template<typename Type>
	bool Write(const char* format, Type value);

	template<typename Type>
	bool WriteLine(const char* format, Type value);
};

inline CLegacyOut::CLegacyOut(): CLegacyOut(CFile(stdout))
{}

inline CLegacyOut::CLegacyOut(const CFile& out) : out_(out)
{
	setvbuf(out_, nullptr, _IONBF, 0u);
}

inline CLegacyOut::CLegacyOut(CLegacyOut&& move) noexcept            = default;

inline CLegacyOut& CLegacyOut::operator=(CLegacyOut&& move) noexcept = default;

inline CLegacyOut::~CLegacyOut()                                     = default;

inline bool CLegacyOut::Write(const char value)
{
	return Write<char>("%c", value);
}

inline bool CLegacyOut::Write(const std::string& value)
{
	return Write<const char*>("%s", value.c_str());
}

inline bool CLegacyOut::WriteLine(const char value)
{
	return WriteLine<char>("%c", value);
}

inline bool CLegacyOut::WriteLine(const std::string& value)
{
	return WriteLine<const char*>("%s", value.c_str());
}

inline bool CLegacyOut::BreakLine()
{
	return Write('\n');
}

template<typename Type>
bool CLegacyOut::Write(const char* const format, Type value)
{
	return fprintf(out_, format, value) ? true : false;
}

template<typename Type>
bool CLegacyOut::WriteLine(const char* const format, Type value)
{
	return Write(format, value) && BreakLine() ? true : false;
}

inline CLegacyOut LCout;
