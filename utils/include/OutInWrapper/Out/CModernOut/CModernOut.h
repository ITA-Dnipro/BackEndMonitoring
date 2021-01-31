#pragma once
#include <iostream>

#include "../Interfaces/IWriter.h"

class CModernOut final : public IWriter
{
public:
	CModernOut();
	explicit CModernOut(std::ostream& out);
	CModernOut(const CModernOut& copy) = delete;
	CModernOut(CModernOut&& move) noexcept;

	CModernOut& operator=(const CModernOut& copy) = delete;
	CModernOut& operator=(CModernOut&& move) noexcept;
	
	~CModernOut() override;
	
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
	std::reference_wrapper<std::ostream> out_;

	template<typename Type>
	bool Write(Type value);

	template<typename Type>
	bool WriteLine(Type value);
};

inline CModernOut::CModernOut(): CModernOut(std::cout) {}

inline CModernOut::CModernOut(std::ostream& out): out_(out) {}

inline CModernOut::CModernOut(CModernOut&& move) noexcept            = default;

inline CModernOut& CModernOut::operator=(CModernOut&& move) noexcept = default;

inline CModernOut::~CModernOut()                                     = default;

inline bool CModernOut::Write(const char value)
{
	return Write<char>(value);
}

inline bool CModernOut::Write(const bool value)
{
	return out_.get() << std::boolalpha << value ? true : false;
}

inline bool CModernOut::Write(const short value)
{
	return Write(static_cast<int>(value));
}

inline bool CModernOut::Write(const int value)
{
	return Write(static_cast<long>(value));
}

inline bool CModernOut::Write(const long value)
{
	return Write(static_cast<long long>(value));
}

inline bool CModernOut::Write(const long long value)
{
	return Write<long long>(value);
}

inline bool CModernOut::Write(const unsigned short value)
{
	return Write(static_cast<unsigned>(value));
}

inline bool CModernOut::Write(const unsigned value)
{
	return Write(static_cast<unsigned long>(value));
}

inline bool CModernOut::Write(const unsigned long value)
{
	return Write(static_cast<unsigned long long>(value));
}

inline bool CModernOut::Write(const unsigned long long value)
{
	return Write<unsigned long long>(value);
}

inline bool CModernOut::Write(const char* value)
{
	return Write(std::string(value));
}

inline bool CModernOut::Write(char* value)
{
	return Write(std::string(value));
}

inline bool CModernOut::Write(const std::string& value)
{
	return Write<std::string>(value);
}

inline bool CModernOut::Write(const float value)
{
	return Write(static_cast<double>(value));
}

inline bool CModernOut::Write(const double value)
{
	return Write(static_cast<long double>(value));
}

inline bool CModernOut::Write(const long double value)
{
	return out_.get() << std::fixed << value ? true : false;
}

inline bool CModernOut::WriteLine(const char value)
{
	return WriteLine<char>(value);
}

inline bool CModernOut::WriteLine(const bool value)
{
	return out_.get() << std::boolalpha << value << std::endl ? true : false;
}

inline bool CModernOut::WriteLine(const short value)
{
	return WriteLine(static_cast<int>(value));
}

inline bool CModernOut::WriteLine(const int value)
{
	return WriteLine(static_cast<long>(value));
}

inline bool CModernOut::WriteLine(const long value)
{
	return WriteLine(static_cast<long long>(value));
}

inline bool CModernOut::WriteLine(const long long value)
{
	return WriteLine<long long>(value);
}

inline bool CModernOut::WriteLine(const unsigned short value)
{
	return WriteLine(static_cast<unsigned>(value));
}

inline bool CModernOut::WriteLine(const unsigned value)
{
	return WriteLine(static_cast<unsigned long>(value));
}

inline bool CModernOut::WriteLine(const unsigned long value)
{
	return WriteLine(static_cast<unsigned long long>(value));
}

inline bool CModernOut::WriteLine(const unsigned long long value)
{
	return WriteLine<unsigned long long>(value);
}

inline bool CModernOut::WriteLine(const char* value)
{
	return WriteLine<const char*>(value);
}

inline bool CModernOut::WriteLine(char* value)
{
	return WriteLine<char*>(value);
}

inline bool CModernOut::WriteLine(const std::string& value)
{
	return WriteLine(value.c_str());
}

inline bool CModernOut::WriteLine(const float value)
{
	return WriteLine(static_cast<double>(value));
}

inline bool CModernOut::WriteLine(const double value)
{
	return WriteLine(static_cast<long double>(value));
}

inline bool CModernOut::WriteLine(const long double value)
{
	return out_.get() << std::fixed << value << std::endl ? true : false;
}

inline bool CModernOut::BreakLine()
{
	return Write('\n');
}

template<typename Type>
bool CModernOut::Write(Type value)
{
	return out_.get() << value ? true : false;
}

template<typename Type>
bool CModernOut::WriteLine(Type value)
{
	return Write(value) && BreakLine() ? true : false;
}

inline CModernOut MCout;
