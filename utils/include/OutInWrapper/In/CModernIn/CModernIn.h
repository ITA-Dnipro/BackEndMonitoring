#pragma once
#include <iostream>

#include "../Interfaces/IReader.h"

class CModernIn : public IReader
{
public:
	CModernIn();
	explicit CModernIn(std::istream& in);
	CModernIn(const CModernIn& copy) = delete;
	CModernIn(CModernIn&&) noexcept;
	
	~CModernIn() override;
	
	bool Read(char& value) override;
	bool Read(std::string& value) override;
	
	bool ReadLine(std::string& value) override;
private:
	std::reference_wrapper<std::istream> in_;

	template<typename Type>
	bool Read(Type& value);
	[[nodiscard]] bool Ignore() const;
};

inline CModernIn::CModernIn(): CModernIn(std::cin)
{}

inline CModernIn::CModernIn(std::istream& in): in_(in)
{}

inline CModernIn::CModernIn(CModernIn&&) noexcept = default;
inline CModernIn::~CModernIn()                    = default;

inline bool CModernIn::Read(char& value)
{
	return Read<char>(value);
}

inline bool CModernIn::Read(std::string& value)
{
	return Read<std::string>(value);
}

inline bool CModernIn::ReadLine(std::string& value)
{
	return std::getline(in_.get(), value) ? true : false;
}

template<typename Type>
bool CModernIn::Read(Type& value)
{
	return in_.get() >> value && Ignore() ? true : false;
}

inline bool CModernIn::Ignore() const
{
	return in_.get()
	          .ignore(std::numeric_limits<std::streamsize>::max(),
	                  '\n')
		       ? true
		       : false;
}

inline CModernIn MCin;
