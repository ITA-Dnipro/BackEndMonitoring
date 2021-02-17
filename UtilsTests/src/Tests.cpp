#include <gtest/gtest.h>

#include "CNumericTypesParser.h"
#include "CStringCleaner.h"
#include "CXMLDataReader.h"
#include "StrToNumWrapper.h"

struct CXMLDataReaderTestFixture : public testing::Test
{
public:
	CXMLDataReaderTestFixture() = default;

	~CXMLDataReaderTestFixture() override = default;

	int resultInt = 0;
	bool resultBool = false;
	std::unique_ptr<CXMLDataReader> reader = std::make_unique<CXMLDataReader>();
};

TEST_F(CXMLDataReaderTestFixture, TryToBoolTestDisable)
{
	ASSERT_TRUE(this->reader->TryToConvertToBool("disable", this->resultBool));
	ASSERT_FALSE(this->resultBool);
}

TEST_F(CXMLDataReaderTestFixture, TryToBoolTestEnable)
{
	ASSERT_TRUE(this->reader->TryToConvertToBool("enable", this->resultBool));
	ASSERT_TRUE(this->resultBool);
}

TEST_F(CXMLDataReaderTestFixture, TryToBoolTestFenableck)
{
	ASSERT_FALSE(this->reader->TryToConvertToBool("FenableCK", this->resultBool));
	ASSERT_FALSE(this->resultBool);
}

TEST_F(CXMLDataReaderTestFixture, TryToBoolTestEmpty)
{
	ASSERT_FALSE(this->reader->TryToConvertToBool("", this->resultBool));
	ASSERT_FALSE(this->resultBool);
}

TEST_F(CXMLDataReaderTestFixture, TryToConvertToIntegerOne)
{
	ASSERT_TRUE(this->reader->TryToConvertToInteger("1", this->resultInt));
	ASSERT_EQ(1, this->resultInt);
}

TEST_F(CXMLDataReaderTestFixture, TryToConvertToIntegerMinusOne) {
	ASSERT_TRUE(this->reader->TryToConvertToInteger("-1", this->resultInt));
	ASSERT_EQ(-1, this->resultInt);
}

TEST_F(CXMLDataReaderTestFixture, TryToConvertToIntegerMax)
{
	constexpr auto temp = std::numeric_limits<int>::max();
	ASSERT_TRUE(this->reader->TryToConvertToInteger
		(std::to_string(temp), this->resultInt));
	ASSERT_EQ(temp, this->resultInt);
}

TEST_F(CXMLDataReaderTestFixture, TryToConvertToIntegerMinusMax)
{
	constexpr auto temp = -std::numeric_limits<int>::max();
	ASSERT_TRUE(this->reader->TryToConvertToInteger
		(std::to_string(temp), this->resultInt));
	ASSERT_EQ(temp, this->resultInt);
}

TEST_F(CXMLDataReaderTestFixture, TryToConvertToIntegerMinusFortyOne)
{
	ASSERT_TRUE(this->reader->TryToConvertToInteger("-41", this->resultInt));
	ASSERT_EQ(-41, this->resultInt);
}

struct CStringCleanerTestFixture : public testing::Test
{
public:
	CStringCleanerTestFixture() = default;

	~CStringCleanerTestFixture() override = default;

	std::string testStr			  = "\n\t\n  \t\n TestString";
	std::string lowerStr		  = "\n\t\n  \t\n teststring";
	std::string trimmedStr		  = "TestString";
	std::string trimmedLowerStr   = "teststring";
	std::unique_ptr<CStringCleaner> stringCleaner
		= std::make_unique<CStringCleaner>(testStr);
};

TEST_F(CStringCleanerTestFixture, GetOriginalString)
{
	ASSERT_STREQ(this->testStr.c_str(),
		this->stringCleaner->GetOriginalString().c_str());
}

TEST_F(CStringCleanerTestFixture, GetTrimedString)
{
	ASSERT_STREQ
		(this->stringCleaner->GetOriginalString().c_str(),
			this->testStr.c_str());
	ASSERT_STREQ(this->stringCleaner->GetTrimedString().c_str(),
		this->trimmedStr.c_str());
}

TEST_F(CStringCleanerTestFixture, GetTrimedLowerString)
{
	ASSERT_STREQ
	(this->stringCleaner->GetOriginalString().c_str(),
		this->testStr.c_str());
	ASSERT_STREQ(this->stringCleaner->GetTrimmedLowercaseString().c_str(),
		this->trimmedLowerStr.c_str());
}

TEST_F(CStringCleanerTestFixture, GetLowerString)
{
	ASSERT_STREQ
	(this->stringCleaner->GetOriginalString().c_str(),
		this->testStr.c_str());
	ASSERT_STREQ(this->stringCleaner->GetLowercaseString().c_str(),
		this->lowerStr.c_str());
}

struct CNumericTypesParserTestFixture : public testing::Test
{
public:
	CNumericTypesParserTestFixture() = default;

	~CNumericTypesParserTestFixture() override = default;

	int naturalTest			    = 12;
	int negativeTest		    = -12;
	double floatTest		    = 12.12;
	double negativeFloatTest    = -12.12;
	int zeroTest			    = 0;
	std::string failStringTest  = "Fail";
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

TEST_F(CNumericTypesParserTestFixture, AsNaturalDoubleFail)
{
	const auto str = std::to_string(this->floatTest);
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

TEST_F(CNumericTypesParserTestFixture, AsNaturalLongDoubleFail)
{
	const auto str = std::to_string(this->floatTest);
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

TEST_F(CNumericTypesParserTestFixture, AsNaturalFloatFail)
{
	const auto str = std::to_string(this->floatTest);
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

//----------------------------------------------------------------

struct CStrToNumWrapperTestTestFixture : public testing::Test
{
public:
	CStrToNumWrapperTestTestFixture() = default;

	~CStrToNumWrapperTestTestFixture() override = default;

	int naturalTest = 12;
	int negativeTest = -12;
	double floatTest = 12.12;
	double negativeFloatTest = -12.12;
	int zeroTest = 0;
	std::string failStringTest = "Fail";
	std::string emptyStringTest;
};

TEST_F(CStrToNumWrapperTestTestFixture, TryStoiPositiveSuccess)
{
	int value;
	ASSERT_TRUE(StrToNumWrapper::TryStoi(std::to_string(this->naturalTest), value));
	ASSERT_EQ(value, this->naturalTest);
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStoiNegativeSuccess)
{
	int value;
	ASSERT_TRUE(StrToNumWrapper::TryStoi(std::to_string(this->negativeTest), value));
	ASSERT_EQ(value, this->negativeTest);
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStoiZeroSuccess)
{
	int value;
	ASSERT_TRUE(StrToNumWrapper::TryStoi(std::to_string(this->zeroTest), value));
	ASSERT_EQ(value, this->zeroTest);
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStoiStringFail)
{
	int value;
	ASSERT_FALSE(StrToNumWrapper::TryStoi(this->failStringTest, value));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStoiEmptyFail)
{
	int value;
	ASSERT_FALSE(StrToNumWrapper::TryStoi(this->emptyStringTest, value));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStoulPositiveSuccess)
{
	unsigned value;
	ASSERT_TRUE(StrToNumWrapper::TryStoul(std::to_string(this->naturalTest), value));
	ASSERT_EQ(value, this->naturalTest);
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStoulZeroSuccess)
{
	unsigned value;
	ASSERT_TRUE(StrToNumWrapper::TryStoul(std::to_string(this->zeroTest), value));
	ASSERT_EQ(value, this->zeroTest);
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStoulStringFail)
{
	unsigned value;
	ASSERT_FALSE(StrToNumWrapper::TryStoul(this->failStringTest, value));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStoulEmptyFail)
{
	unsigned value;
	ASSERT_FALSE(StrToNumWrapper::TryStoul(this->emptyStringTest, value));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStollPositiveSuccess)
{
	long long value;
	ASSERT_TRUE(StrToNumWrapper::TryStoll(std::to_string(this->naturalTest), value));
	ASSERT_EQ(value, this->naturalTest);
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStollNegativeSuccess)
{
	long long value;
	ASSERT_TRUE(StrToNumWrapper::TryStoll(std::to_string(this->negativeTest), value));
	ASSERT_EQ(value, this->negativeTest);
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStollZeroSuccess)
{
	long long value;
	ASSERT_TRUE(StrToNumWrapper::TryStoll(std::to_string(this->zeroTest), value));
	ASSERT_EQ(value, this->zeroTest);
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStollStringFail)
{
	long long value;
	ASSERT_FALSE(StrToNumWrapper::TryStoll(this->failStringTest, value));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStollEmptyFail)
{
	long long value;
	ASSERT_FALSE(StrToNumWrapper::TryStoll(this->emptyStringTest, value));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStoullPositiveSuccess)
{
	unsigned long long value;
	ASSERT_TRUE(StrToNumWrapper::TryStoull(std::to_string(this->naturalTest), value));
	ASSERT_EQ(value, this->naturalTest);
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStoullZeroSuccess)
{
	unsigned long long value;
	ASSERT_TRUE(StrToNumWrapper::TryStoull(std::to_string(this->zeroTest), value));
	ASSERT_EQ(value, this->zeroTest);
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStoullStringFail)
{
	unsigned long long value;
	ASSERT_FALSE(StrToNumWrapper::TryStoull(this->failStringTest, value));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStoullEmptyFail)
{
	unsigned long long value;
	ASSERT_FALSE(StrToNumWrapper::TryStoull(this->emptyStringTest, value));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStofPositiveSuccess)
{
	float value;
	ASSERT_TRUE(StrToNumWrapper::TryStof(std::to_string(this->floatTest), value));
	ASSERT_FLOAT_EQ(value, static_cast<float>(this->floatTest));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStofNegativeSuccess)
{
	float value;
	ASSERT_TRUE(StrToNumWrapper::TryStof(std::to_string(this->negativeFloatTest), value));
	ASSERT_FLOAT_EQ(value, this->negativeFloatTest);
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStofZeroSuccess)
{
	float value;
	ASSERT_TRUE(StrToNumWrapper::TryStof(std::to_string(this->zeroTest), value));
	ASSERT_FLOAT_EQ(value, static_cast<float>(this->zeroTest));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStofStringFail)
{
	float value;
	ASSERT_FALSE(StrToNumWrapper::TryStof(this->failStringTest, value));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStofEmptyFail)
{
	float value;
	ASSERT_FALSE(StrToNumWrapper::TryStof(this->emptyStringTest, value));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStodPositiveSuccess)
{
	double value;
	ASSERT_TRUE(StrToNumWrapper::TryStod(std::to_string(this->floatTest), value));
	ASSERT_DOUBLE_EQ(value, static_cast<double>(this->floatTest));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStodNegativeSuccess)
{
	double value;
	ASSERT_TRUE(StrToNumWrapper::TryStod(std::to_string(this->negativeFloatTest), value));
	ASSERT_DOUBLE_EQ(value, static_cast<double>(this->negativeFloatTest));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStodZeroSuccess)
{
	double value;
	ASSERT_TRUE(StrToNumWrapper::TryStod(std::to_string(this->zeroTest), value));
	ASSERT_DOUBLE_EQ(value, static_cast<double>(this->zeroTest));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStodStringFail)
{
	double value;
	ASSERT_FALSE(StrToNumWrapper::TryStod(this->failStringTest, value));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStodEmptyFail)
{
	double value;
	ASSERT_FALSE(StrToNumWrapper::TryStod(this->emptyStringTest, value));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStoldPositiveSuccess)
{
	long double value;
	ASSERT_TRUE(StrToNumWrapper::TryStold(std::to_string(this->floatTest), value));
	ASSERT_DOUBLE_EQ(value, static_cast<long double>(this->floatTest));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStoldNegativeSuccess)
{
	long double value;
	ASSERT_TRUE(StrToNumWrapper::TryStold(std::to_string(this->negativeFloatTest), value));
	ASSERT_DOUBLE_EQ(value, static_cast<long double>(this->negativeFloatTest));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStoldZeroSuccess)
{
	long double value;
	ASSERT_TRUE(StrToNumWrapper::TryStold(std::to_string(this->zeroTest), value));
	ASSERT_DOUBLE_EQ(value, static_cast<long double>(this->zeroTest));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStoldStringFail)
{
	long double value;
	ASSERT_FALSE(StrToNumWrapper::TryStold(this->failStringTest, value));
}

TEST_F(CStrToNumWrapperTestTestFixture, TryStoldEmptyFail)
{
	long double value;
	ASSERT_FALSE(StrToNumWrapper::TryStold(this->emptyStringTest, value));
}
