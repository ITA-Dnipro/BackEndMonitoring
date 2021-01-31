#pragma once
#include <iostream>

#include "../Interfaces/IReader.h"

class CModernIn final : public IReader
{
public:
	CModernIn();
	explicit CModernIn(std::istream& in);
	CModernIn(const CModernIn& copy) = delete;
	CModernIn(CModernIn&&) noexcept;
	
	~CModernIn() override;
	
	bool Read(bool& value) override;
	bool Read(char& value) override;
	bool Read(short& value) override;
	bool Read(int& value) override;
	bool Read(long& value) override;
	bool Read(long long& value) override;
	bool Read(unsigned short& value) override;
	bool Read(unsigned& value) override;
	bool Read(unsigned long& value) override;
	bool Read(unsigned long long& value) override;
	bool Read(float& value) override;
	bool Read(double& value) override;
	bool Read(long double& value) override;
	bool Read(char* value) override;
	bool Read(std::string& value) override;
	
	bool ReadLine(char* value,
		std::streamsize size
			= std::numeric_limits<std::streamsize>::max()) override;
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

inline bool CModernIn::Read(bool& value)
{
	return Read<bool>(value);
}

inline bool CModernIn::Read(char& value)
{
	return Read<char>(value);
}

inline bool CModernIn::Read(short& value)
{
	return Read<short>(value);
}

inline bool CModernIn::Read(int& value)
{
	return Read<int>(value);
}

inline bool CModernIn::Read(long& value)
{
	return Read<long>(value);
}

inline bool CModernIn::Read(long long& value)
{
	return Read<long long>(value);
}

inline bool CModernIn::Read(unsigned short& value)
{
	return Read<unsigned short>(value);
}

inline bool CModernIn::Read(unsigned& value)
{
	return Read<unsigned>(value);
}

inline bool CModernIn::Read(unsigned long& value)
{
	return Read<unsigned long>(value);
}

inline bool CModernIn::Read(unsigned long long& value)
{
	return Read<unsigned long long>(value);
}

inline bool CModernIn::Read(float& value)
{
	return Read<float>(value);
}

inline bool CModernIn::Read(double& value)
{
	return Read<double>(value);
}

inline bool CModernIn::Read(long double& value)
{
	return Read<long double>(value);
}

inline bool CModernIn::Read(char* value)
{
	return Read<char*>(value);
}

inline bool CModernIn::Read(std::string& value)
{
	return Read<std::string>(value);
}

inline bool CModernIn::ReadLine(char* value, const std::streamsize size) {
	return in_.get().getline(value, size) ? true : false;
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
