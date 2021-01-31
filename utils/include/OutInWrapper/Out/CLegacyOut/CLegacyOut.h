#pragma once
#include "../Interfaces/IWriter.h"

class CLegacyOut final : public IWriter
{
public:
	CLegacyOut();
	explicit CLegacyOut(FILE* out);
	CLegacyOut(const CLegacyOut& copy) = delete;
	CLegacyOut(CLegacyOut&& move) noexcept;

	CLegacyOut& operator=(const CLegacyOut& copy) = delete;
	CLegacyOut& operator=(CLegacyOut&& move) noexcept;
	~CLegacyOut() override;
	
	bool Write(char value) override;
	bool Write(bool value) override;
	bool Write(short value) override;
	bool Write(int value) override;
	bool Write(long value) override;
	bool Write(long long value) override;
	bool Write(unsigned short value) override;
	bool Write(unsigned value) override;
	bool Write(unsigned long value) override;
	bool Write(unsigned long long value) override;
	bool Write(const char* value) override;
	bool Write(char* value) override;
	bool Write(const std::string& value) override;
	bool Write(float value) override;
	bool Write(double value) override;
	
	bool Write(long double value) override;
	bool WriteLine(char value) override;
	bool WriteLine(bool value) override;
	bool WriteLine(short value) override;
	bool WriteLine(int value) override;
	bool WriteLine(long value) override;
	bool WriteLine(long long value) override;
	bool WriteLine(unsigned short value) override;
	bool WriteLine(unsigned value) override;
	bool WriteLine(unsigned long value) override;
	bool WriteLine(unsigned long long value) override;
	bool WriteLine(const char* value) override;
	bool WriteLine(char* value) override;
	bool WriteLine(const std::string& value) override;
	bool WriteLine(float value) override;
	bool WriteLine(double value) override;
	bool WriteLine(long double value) override;
	
	bool BreakLine() override;

private:
	std::reference_wrapper<FILE> out_;

	template<typename Type>
	bool Write(const char* format, Type value);

	template<typename Type>
	bool WriteLine(const char* format, Type value);
};

inline CLegacyOut::CLegacyOut(): CLegacyOut(stdout)
{}

inline CLegacyOut::CLegacyOut(FILE* out): out_(*out)
{}

inline CLegacyOut::CLegacyOut(CLegacyOut&& move) noexcept            = default;

inline CLegacyOut& CLegacyOut::operator=(CLegacyOut&& move) noexcept = default;

inline CLegacyOut::~CLegacyOut()                                     = default;

inline bool CLegacyOut::Write(const char value)
{
	return Write<char>("%c", value);
}

inline bool CLegacyOut::Write(const bool value)
{
	return Write(value ? "true" : "false");
}

inline bool CLegacyOut::Write(const short value)
{
	return Write(static_cast<int>(value));
}

inline bool CLegacyOut::Write(const int value)
{
	return Write(static_cast<long>(value));
}

inline bool CLegacyOut::Write(const long value)
{
	return Write(static_cast<long long>(value));
}

inline bool CLegacyOut::Write(const long long value)
{
	return Write<long long>("%lli", value);
}

inline bool CLegacyOut::Write(const unsigned short value)
{
	return Write(static_cast<unsigned>(value));
}

inline bool CLegacyOut::Write(const unsigned value)
{
	return Write(static_cast<unsigned long>(value));
}

inline bool CLegacyOut::Write(const unsigned long value)
{
	return Write(static_cast<unsigned long long>(value));
}

inline bool CLegacyOut::Write(const unsigned long long value)
{
	return Write<unsigned long long>("%llu", value);
}

inline bool CLegacyOut::Write(const char* value)
{
	return Write<const char*>("%s", value);
}

inline bool CLegacyOut::Write(char* value)
{
	return Write<char*>("%s", value);
}

inline bool CLegacyOut::Write(const std::string& value)
{
	return Write(value.c_str());
}

inline bool CLegacyOut::Write(const float value)
{
	return Write(static_cast<double>(value));
}

inline bool CLegacyOut::Write(const double value)
{
	return Write(static_cast<long double>(value));
}

inline bool CLegacyOut::Write(const long double value)
{
	return Write<long double>("%lf", value);
}

inline bool CLegacyOut::WriteLine(const char value)
{
	return WriteLine<char>("%c", value);
}

inline bool CLegacyOut::WriteLine(const bool value)
{
	return WriteLine(value ? "true" : "false");
}

inline bool CLegacyOut::WriteLine(const short value)
{
	return WriteLine(static_cast<int>(value));
}

inline bool CLegacyOut::WriteLine(const int value)
{
	return WriteLine(static_cast<long>(value));
}

inline bool CLegacyOut::WriteLine(const long value)
{
	return WriteLine(static_cast<long long>(value));
}

inline bool CLegacyOut::WriteLine(const long long value)
{
	return WriteLine<long long>("%lli", value);
}

inline bool CLegacyOut::WriteLine(const unsigned short value)
{
	return WriteLine(static_cast<unsigned>(value));
}

inline bool CLegacyOut::WriteLine(const unsigned value)
{
	return WriteLine(static_cast<unsigned long>(value));
}

inline bool CLegacyOut::WriteLine(const unsigned long value)
{
	return WriteLine(static_cast<unsigned long long>(value));
}

inline bool CLegacyOut::WriteLine(const unsigned long long value)
{
	return WriteLine<unsigned long long>("%llu", value);
}

inline bool CLegacyOut::WriteLine(const char* value)
{
	return WriteLine<const char*>("%s", value);
}

inline bool CLegacyOut::WriteLine(char* value)
{
	return WriteLine<char*>("%s", value);
}

inline bool CLegacyOut::WriteLine(const std::string& value)
{
	return WriteLine(value.c_str());
}

inline bool CLegacyOut::WriteLine(const float value)
{
	return WriteLine(static_cast<double>(value));
}

inline bool CLegacyOut::WriteLine(const double value)
{
	return WriteLine(static_cast<long double>(value));
}

inline bool CLegacyOut::WriteLine(const long double value)
{
	return WriteLine<long double>("%lf", value);
}

inline bool CLegacyOut::BreakLine()
{
	return Write('\n');
}

template<typename Type>
bool CLegacyOut::Write(const char* const format, Type value)
{
	return fprintf(&out_.get(), format, value) ? true : false;
}

template<typename Type>
bool CLegacyOut::WriteLine(const char* const format, Type value)
{
	return Write(format, value) && BreakLine() ? true : false;
}

inline CLegacyOut LCout;
