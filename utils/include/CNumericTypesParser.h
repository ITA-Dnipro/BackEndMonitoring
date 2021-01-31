#pragma once

class CNumericTypesParser {
  public:
    CNumericTypesParser(const std::string& value);
    CNumericTypesParser(const CNumericTypesParser& other) = default;
    CNumericTypesParser(CNumericTypesParser&& other) = default;
    ~CNumericTypesParser() noexcept = default;

    bool AsNaturalNumber(unsigned int&) const;
    bool AsNaturalNumber(unsigned long long&) const;
    bool AsNaturalNumber(float&) const;
    bool AsNaturalNumber(double&) const;
    bool AsNaturalNumber(long double&) const;

    bool AsUnsignedNumber(unsigned int&) const;
    bool AsUnsignedNumber(unsigned long long&) const;
    bool AsUnsignedNumber(float&) const;
    bool AsUnsignedNumber(double&) const;
    bool AsUnsignedNumber(long double&) const;

    bool AsNumber(int&) const;
    bool AsNumber(long long&) const;
    bool AsNumber(float&) const;
    bool AsNumber(double&) const;
    bool AsNumber(long double&) const;
  private:
    bool IsUnsignedIntagerNumber() const;
    bool IsUnsignedFloatingPointNumber() const;
    bool IsIntagerNumber() const;
    bool IsFloatingPointNumber() const;
    bool IsValidScientificNotaton(
            std::string::const_iterator scientific_part_begin,
            std::string::const_iterator scientific_part_end) const;

    const std::string m_value;
};
