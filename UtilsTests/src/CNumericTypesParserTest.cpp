#include <gtest/gtest.h>

#include "CNumericTypesParser.h"

struct CNumericTypesParserTestFixture : public testing::Test
{
public:
	CNumericTypesParserTestFixture() = default;

	~CNumericTypesParserTestFixture() override = default;

	int naturalTest = 12;
	int negativeTest = -12;
	double floatTest = 12.12;
	double negativeFloatTest = -12.12;
	int zeroTest = 0;
	std::string failStringTest = "Fail";
	std::string emptyStringTest;
};

//----------------------------------------------------------------

TEST_F(CNumericTypesParserTestFixture, AsNaturalUnsignedSuccess)
{
	const auto str = std::to_string(this->naturalTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	unsigned result;

	ASSERT_TRUE(parser->AsNaturalNumber(result));
	ASSERT_EQ(result, this->naturalTest);
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalUnsignedStringFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->failStringTest);
	unsigned result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalUnsignedEmptyFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->emptyStringTest);
	unsigned result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalUnsignedLongLongSuccess)
{
	const auto str = std::to_string(this->naturalTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	unsigned long long result;

	ASSERT_TRUE(parser->AsNaturalNumber(result));
	ASSERT_EQ(result, this->naturalTest);
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalUnsignedLongLongStringFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->failStringTest);
	unsigned long long result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalUnsignedLongLongEmptyFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->emptyStringTest);
	unsigned long long result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalFloatSuccess)
{
	const auto str = std::to_string(this->naturalTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	float result;

	ASSERT_TRUE(parser->AsNaturalNumber(result));
	ASSERT_FLOAT_EQ(result, static_cast<float>(this->naturalTest));
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalDoubleSuccess)
{
	const auto str = std::to_string(this->naturalTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	double result;

	ASSERT_TRUE(parser->AsNaturalNumber(result));
	ASSERT_DOUBLE_EQ(result, static_cast<double>(this->naturalTest));
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalLongDoubleSuccess)
{
	const auto str = std::to_string(this->naturalTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	long double result;

	ASSERT_TRUE(parser->AsNaturalNumber(result));
	ASSERT_DOUBLE_EQ(result, static_cast<long double>(this->naturalTest));
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalDoubleNegativeFail)
{
	const auto str = std::to_string(this->negativeFloatTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	double result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalDoubleZeroFail)
{
	const auto str = std::to_string(this->zeroTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	double result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalDoubleStringFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->failStringTest);
	double result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalDoubleEmptyFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->emptyStringTest);
	double result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalLongDoubleNegativeFail)
{
	const auto str = std::to_string(this->negativeFloatTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	long double result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalLongDoubleZeroFail)
{
	const auto str = std::to_string(this->zeroTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	long double result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalLongDoubleStringFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->failStringTest);
	long double result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalLongDoubleEmptyFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->emptyStringTest);
	long double result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalFloatNegativeFail)
{
	const auto str = std::to_string(this->negativeFloatTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	float result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalFloatZeroFail)
{
	const auto str = std::to_string(this->zeroTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	float result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalFloatStringFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->failStringTest);
	float result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNaturalFloatEmptyFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->emptyStringTest);
	float result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

//----------------------------------------------------------------

TEST_F(CNumericTypesParserTestFixture, AsUnsignedUnsignedSuccess)
{
	const auto str = std::to_string(this->naturalTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	unsigned result;

	ASSERT_TRUE(parser->AsUnsignedNumber(result));
	ASSERT_EQ(result, this->naturalTest);
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedUnsignedStringFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->failStringTest);
	unsigned result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedUnsignedEmptyFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->emptyStringTest);
	unsigned result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedUnsignedLongLongSuccess)
{
	const auto str = std::to_string(this->naturalTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	unsigned long long result;

	ASSERT_TRUE(parser->AsUnsignedNumber(result));
	ASSERT_EQ(result, this->naturalTest);
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedUnsignedLongLongStringFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->failStringTest);
	unsigned long long result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedUnsignedLongLongEmptyFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->emptyStringTest);
	unsigned long long result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedFloatSuccess)
{
	const auto str = std::to_string(this->floatTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	float result;

	ASSERT_TRUE(parser->AsUnsignedNumber(result));
	ASSERT_FLOAT_EQ(result, static_cast<float>(this->floatTest));
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedDoubleSuccess)
{
	const auto str = std::to_string(this->floatTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	double result;

	ASSERT_TRUE(parser->AsUnsignedNumber(result));
	ASSERT_DOUBLE_EQ(result, static_cast<double>(this->floatTest));
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedLongDoubleSuccess)
{
	const auto str = std::to_string(this->floatTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	long double result;

	ASSERT_TRUE(parser->AsUnsignedNumber(result));
	ASSERT_DOUBLE_EQ(result, static_cast<long double>(this->floatTest));
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedDoubleNegativeFail)
{
	const auto str = std::to_string(this->negativeFloatTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	double result;

	ASSERT_FALSE(parser->AsUnsignedNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedDoubleZeroSuccess)
{
	const auto str = std::to_string(this->zeroTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	double result;

	ASSERT_TRUE(parser->AsUnsignedNumber(result));
	ASSERT_DOUBLE_EQ(result, static_cast<long double>(this->zeroTest));
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedDoubleStringFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->failStringTest);
	double result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedDoubleEmptyFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->emptyStringTest);
	double result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedLongDoubleNegativeFail)
{
	const auto str = std::to_string(this->negativeFloatTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	long double result;

	ASSERT_FALSE(parser->AsUnsignedNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedLongDoubleZeroSuccess)
{
	const auto str = std::to_string(this->zeroTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	long double result;

	ASSERT_TRUE(parser->AsUnsignedNumber(result));
	ASSERT_DOUBLE_EQ(result, static_cast<long double>(this->zeroTest));
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedLongDoubleStringFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->failStringTest);
	long double result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedLongDoubleEmptyFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->emptyStringTest);
	long double result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedFloatNegativeFail)
{
	const auto str = std::to_string(this->negativeFloatTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	float result;

	ASSERT_FALSE(parser->AsUnsignedNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedFloatZeroSuccess)
{
	const auto str = std::to_string(this->zeroTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	float result;

	ASSERT_TRUE(parser->AsUnsignedNumber(result));
	ASSERT_FLOAT_EQ(result, static_cast<float>(this->zeroTest));
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedFloatStringFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->failStringTest);
	float result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsUnsignedFloatEmptyFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->emptyStringTest);
	float result;

	ASSERT_FALSE(parser->AsNaturalNumber(result));
}

//----------------------------------------------------------------

TEST_F(CNumericTypesParserTestFixture, AsNumberIntSuccess)
{
	const auto str = std::to_string(this->naturalTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	int result;

	ASSERT_TRUE(parser->AsNumber(result));
	ASSERT_EQ(result, this->naturalTest);
}

TEST_F(CNumericTypesParserTestFixture, AsNumberIntStringFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->failStringTest);
	int result;

	ASSERT_FALSE(parser->AsNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNumberIntEmptyFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->emptyStringTest);
	int result;

	ASSERT_FALSE(parser->AsNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNumberLongLongSuccess)
{
	const auto str = std::to_string(this->naturalTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	long long result;

	ASSERT_TRUE(parser->AsNumber(result));
	ASSERT_EQ(result, this->naturalTest);
}

TEST_F(CNumericTypesParserTestFixture, AsNumberLongLongStringFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->failStringTest);
	long long result;

	ASSERT_FALSE(parser->AsNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNumberLongLongEmptyFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->emptyStringTest);
	long long result;

	ASSERT_FALSE(parser->AsNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNumberFloatSuccess)
{
	const auto str = std::to_string(this->floatTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	float result;

	ASSERT_TRUE(parser->AsNumber(result));
	ASSERT_FLOAT_EQ(result, static_cast<float>(this->floatTest));
}

TEST_F(CNumericTypesParserTestFixture, AsNumberFloatStringFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->failStringTest);
	float result;

	ASSERT_FALSE(parser->AsNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNumberFloatEmptyFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->emptyStringTest);
	float result;

	ASSERT_FALSE(parser->AsNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNumberDoubleSuccess)
{
	const auto str = std::to_string(this->floatTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	double result;

	ASSERT_TRUE(parser->AsNumber(result));
	ASSERT_DOUBLE_EQ(result, this->floatTest);
}

TEST_F(CNumericTypesParserTestFixture, AsNumberDoubleStringFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->failStringTest);
	double result;

	ASSERT_FALSE(parser->AsNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNumberDoubleEmptyFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->emptyStringTest);
	double result;

	ASSERT_FALSE(parser->AsNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNumberLongDoubleSuccess)
{
	const auto str = std::to_string(this->floatTest);
	const auto parser = std::make_unique<CNumericTypesParser>(str);
	long double result;

	ASSERT_TRUE(parser->AsNumber(result));
	ASSERT_DOUBLE_EQ(result, static_cast<long double>(this->floatTest));
}

TEST_F(CNumericTypesParserTestFixture, AsNumberLongDoubleStringFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->failStringTest);
	long double result;

	ASSERT_FALSE(parser->AsNumber(result));
}

TEST_F(CNumericTypesParserTestFixture, AsNumberLongDoubleEmptyFail)
{
	const auto parser = std::make_unique<CNumericTypesParser>(this->emptyStringTest);
	long double result;

	ASSERT_FALSE(parser->AsNumber(result));
}
