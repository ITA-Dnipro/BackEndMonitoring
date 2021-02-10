#pragma once
#include <iostream>

#include "../Interfaces/IWriter.h"

class CModernOut : public IWriter
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
	bool Write(const std::string& value) override;
	
	bool WriteLine(char value) override;
	bool WriteLine(const std::string& value) override;
	
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

inline bool CModernOut::Write(const std::string& value)
{
	return Write<std::string>(value);
}

inline bool CModernOut::WriteLine(const char value)
{
	return WriteLine<char>(value);
}

inline bool CModernOut::WriteLine(const std::string& value)
{
	return WriteLine(value.c_str());
}

inline bool CModernOut::BreakLine()
{
	return Write('\n');
}

template<typename Type>
bool CModernOut::Write(Type value)
{
	return out_.get() << value << std::flush ? true : false;
}

template<typename Type>
bool CModernOut::WriteLine(Type value)
{
	return Write(value) && out_.get() << std::endl ? true : false;
}

inline CModernOut MCout;
