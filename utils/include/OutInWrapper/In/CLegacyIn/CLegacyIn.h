#pragma once
#include <iostream>

#include "../Interfaces/IReader.h"

class CLegacyIn final : public IReader
{
public:
	CLegacyIn();
	explicit CLegacyIn(FILE* in);
	CLegacyIn(const CLegacyIn& copy) = delete;
	CLegacyIn(CLegacyIn&&) noexcept;

	~CLegacyIn() override;

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
	std::reference_wrapper<FILE> in_;

	template<typename Type>
	bool Read(Type& value);
	template<typename Type>
	bool Read(const char* format, Type& value);
};

inline CLegacyIn::CLegacyIn() : CLegacyIn(stdin)
{}

inline CLegacyIn::CLegacyIn(FILE* in) : in_(*in)
{}

inline CLegacyIn::CLegacyIn(CLegacyIn&&) noexcept = default;
inline CLegacyIn::~CLegacyIn() = default;

inline bool CLegacyIn::Read(bool& value)
{
	return Read<bool>(value);
}

inline bool CLegacyIn::Read(char& value)
{
	return Read<char>("%c", value);
}

inline bool CLegacyIn::Read(short& value)
{
	return Read<short>(value);
}

inline bool CLegacyIn::Read(int& value)
{
	return Read<int>("%d", value);
}

inline bool CLegacyIn::Read(long& value)
{
	return Read<long>("%li", value);
}

inline bool CLegacyIn::Read(long long& value)
{
	return Read<long long>("%lli", value);
}

inline bool CLegacyIn::Read(unsigned short& value)
{
	return Read<unsigned short>(value);
}

inline bool CLegacyIn::Read(unsigned& value)
{
	return Read<unsigned>("%u", value);
}

inline bool CLegacyIn::Read(unsigned long& value)
{
	return Read<unsigned long>("%lu", value);
}

inline bool CLegacyIn::Read(unsigned long long& value)
{
	return Read<unsigned long long>("%llu", value);
}

inline bool CLegacyIn::Read(float& value)
{
	return Read<float>("%f", value);
}

inline bool CLegacyIn::Read(double& value)
{
	return Read<double>("%lf", value);
}

inline bool CLegacyIn::Read(long double& value)
{
	return Read<long double>("%lf", value);
}

inline bool CLegacyIn::Read(char* value)
{
	return Read<char*>("%s", value);
}

inline bool CLegacyIn::Read(std::string& value)
{
	return Read<std::string>("%s", value);
}

inline bool CLegacyIn::ReadLine(char* value, const std::streamsize size) {
	return fgets(value, static_cast<int>(size), &in_.get()) ? true : false;
}

inline bool CLegacyIn::ReadLine(std::string& value)
{
	return fgets(value.data(), value.size(), &in_.get()) ? true : false;
}

template<typename Type>
bool CLegacyIn::Read(const char* const format, Type& value)
{
	return fscanf(&in_.get(), format, &value) ? true : false;
}

template<typename Type>
bool CLegacyIn::Read(Type& value)
{
	int temp;
	if (!Read<int>("%d", temp))
	{
		return false;
	}
	
	try
	{
		value = static_cast<Type>(temp);
	}
	catch (const std::exception&)
	{
		return false;
	}

	return true;
}

inline CLegacyIn LCin;
