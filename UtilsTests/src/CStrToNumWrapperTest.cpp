#include <gtest/gtest.h>

#include "StrToNumWrapper.h"

struct CStrToNumWrapperTestFixture : public testing::Test
{
public:
	CStrToNumWrapperTestFixture() = default;

	~CStrToNumWrapperTestFixture() override = default;

	int naturalTest = 12;
	int negativeTest = -12;
	double floatTest = 12.12;
	double negativeFloatTest = -12.12;
	int zeroTest = 0;
	std::string failStringTest = "Fail";
	std::string emptyStringTest;
};

TEST_F(CStrToNumWrapperTestFixture, TryStoiPositiveSuccess)
{
	int value;
	ASSERT_TRUE(StrToNumWrapper::TryStoi(std::to_string(this->naturalTest), value));
	ASSERT_EQ(value, this->naturalTest);
}

TEST_F(CStrToNumWrapperTestFixture, TryStoiNegativeSuccess)
{
	int value;
	ASSERT_TRUE(StrToNumWrapper::TryStoi(std::to_string(this->negativeTest), value));
	ASSERT_EQ(value, this->negativeTest);
}

TEST_F(CStrToNumWrapperTestFixture, TryStoiZeroSuccess)
{
	int value;
	ASSERT_TRUE(StrToNumWrapper::TryStoi(std::to_string(this->zeroTest), value));
	ASSERT_EQ(value, this->zeroTest);
}

TEST_F(CStrToNumWrapperTestFixture, TryStoiStringFail)
{
	int value;
	ASSERT_FALSE(StrToNumWrapper::TryStoi(this->failStringTest, value));
}

TEST_F(CStrToNumWrapperTestFixture, TryStoiEmptyFail)
{
	int value;
	ASSERT_FALSE(StrToNumWrapper::TryStoi(this->emptyStringTest, value));
}

TEST_F(CStrToNumWrapperTestFixture, TryStoulPositiveSuccess)
{
	unsigned value;
	ASSERT_TRUE(StrToNumWrapper::TryStoul(std::to_string(this->naturalTest), value));
	ASSERT_EQ(value, this->naturalTest);
}

TEST_F(CStrToNumWrapperTestFixture, TryStoulZeroSuccess)
{
	unsigned value;
	ASSERT_TRUE(StrToNumWrapper::TryStoul(std::to_string(this->zeroTest), value));
	ASSERT_EQ(value, this->zeroTest);
}

TEST_F(CStrToNumWrapperTestFixture, TryStoulStringFail)
{
	unsigned value;
	ASSERT_FALSE(StrToNumWrapper::TryStoul(this->failStringTest, value));
}

TEST_F(CStrToNumWrapperTestFixture, TryStoulEmptyFail)
{
	unsigned value;
	ASSERT_FALSE(StrToNumWrapper::TryStoul(this->emptyStringTest, value));
}

TEST_F(CStrToNumWrapperTestFixture, TryStollPositiveSuccess)
{
	long long value;
	ASSERT_TRUE(StrToNumWrapper::TryStoll(std::to_string(this->naturalTest), value));
	ASSERT_EQ(value, this->naturalTest);
}

TEST_F(CStrToNumWrapperTestFixture, TryStollNegativeSuccess)
{
	long long value;
	ASSERT_TRUE(StrToNumWrapper::TryStoll(std::to_string(this->negativeTest), value));
	ASSERT_EQ(value, this->negativeTest);
}

TEST_F(CStrToNumWrapperTestFixture, TryStollZeroSuccess)
{
	long long value;
	ASSERT_TRUE(StrToNumWrapper::TryStoll(std::to_string(this->zeroTest), value));
	ASSERT_EQ(value, this->zeroTest);
}

TEST_F(CStrToNumWrapperTestFixture, TryStollStringFail)
{
	long long value;
	ASSERT_FALSE(StrToNumWrapper::TryStoll(this->failStringTest, value));
}

TEST_F(CStrToNumWrapperTestFixture, TryStollEmptyFail)
{
	long long value;
	ASSERT_FALSE(StrToNumWrapper::TryStoll(this->emptyStringTest, value));
}

TEST_F(CStrToNumWrapperTestFixture, TryStoullPositiveSuccess)
{
	unsigned long long value;
	ASSERT_TRUE(StrToNumWrapper::TryStoull(std::to_string(this->naturalTest), value));
	ASSERT_EQ(value, this->naturalTest);
}

TEST_F(CStrToNumWrapperTestFixture, TryStoullZeroSuccess)
{
	unsigned long long value;
	ASSERT_TRUE(StrToNumWrapper::TryStoull(std::to_string(this->zeroTest), value));
	ASSERT_EQ(value, this->zeroTest);
}

TEST_F(CStrToNumWrapperTestFixture, TryStoullStringFail)
{
	unsigned long long value;
	ASSERT_FALSE(StrToNumWrapper::TryStoull(this->failStringTest, value));
}

TEST_F(CStrToNumWrapperTestFixture, TryStoullEmptyFail)
{
	unsigned long long value;
	ASSERT_FALSE(StrToNumWrapper::TryStoull(this->emptyStringTest, value));
}

TEST_F(CStrToNumWrapperTestFixture, TryStofPositiveSuccess)
{
	float value;
	ASSERT_TRUE(StrToNumWrapper::TryStof(std::to_string(this->floatTest), value));
	ASSERT_FLOAT_EQ(value, static_cast<float>(this->floatTest));
}

TEST_F(CStrToNumWrapperTestFixture, TryStofNegativeSuccess)
{
	float value;
	ASSERT_TRUE(StrToNumWrapper::TryStof(std::to_string(this->negativeFloatTest), value));
	ASSERT_FLOAT_EQ(value, this->negativeFloatTest);
}

TEST_F(CStrToNumWrapperTestFixture, TryStofZeroSuccess)
{
	float value;
	ASSERT_TRUE(StrToNumWrapper::TryStof(std::to_string(this->zeroTest), value));
	ASSERT_FLOAT_EQ(value, static_cast<float>(this->zeroTest));
}

TEST_F(CStrToNumWrapperTestFixture, TryStofStringFail)
{
	float value;
	ASSERT_FALSE(StrToNumWrapper::TryStof(this->failStringTest, value));
}

TEST_F(CStrToNumWrapperTestFixture, TryStofEmptyFail)
{
	float value;
	ASSERT_FALSE(StrToNumWrapper::TryStof(this->emptyStringTest, value));
}

TEST_F(CStrToNumWrapperTestFixture, TryStodPositiveSuccess)
{
	double value;
	ASSERT_TRUE(StrToNumWrapper::TryStod(std::to_string(this->floatTest), value));
	ASSERT_DOUBLE_EQ(value, static_cast<double>(this->floatTest));
}

TEST_F(CStrToNumWrapperTestFixture, TryStodNegativeSuccess)
{
	double value;
	ASSERT_TRUE(StrToNumWrapper::TryStod(std::to_string(this->negativeFloatTest), value));
	ASSERT_DOUBLE_EQ(value, static_cast<double>(this->negativeFloatTest));
}

TEST_F(CStrToNumWrapperTestFixture, TryStodZeroSuccess)
{
	double value;
	ASSERT_TRUE(StrToNumWrapper::TryStod(std::to_string(this->zeroTest), value));
	ASSERT_DOUBLE_EQ(value, static_cast<double>(this->zeroTest));
}

TEST_F(CStrToNumWrapperTestFixture, TryStodStringFail)
{
	double value;
	ASSERT_FALSE(StrToNumWrapper::TryStod(this->failStringTest, value));
}

TEST_F(CStrToNumWrapperTestFixture, TryStodEmptyFail)
{
	double value;
	ASSERT_FALSE(StrToNumWrapper::TryStod(this->emptyStringTest, value));
}

TEST_F(CStrToNumWrapperTestFixture, TryStoldPositiveSuccess)
{
	long double value;
	ASSERT_TRUE(StrToNumWrapper::TryStold(std::to_string(this->floatTest), value));
	ASSERT_DOUBLE_EQ(value, static_cast<long double>(this->floatTest));
}

TEST_F(CStrToNumWrapperTestFixture, TryStoldNegativeSuccess)
{
	long double value;
	ASSERT_TRUE(StrToNumWrapper::TryStold(std::to_string(this->negativeFloatTest), value));
	ASSERT_DOUBLE_EQ(value, static_cast<long double>(this->negativeFloatTest));
}

TEST_F(CStrToNumWrapperTestFixture, TryStoldZeroSuccess)
{
	long double value;
	ASSERT_TRUE(StrToNumWrapper::TryStold(std::to_string(this->zeroTest), value));
	ASSERT_DOUBLE_EQ(value, static_cast<long double>(this->zeroTest));
}

TEST_F(CStrToNumWrapperTestFixture, TryStoldStringFail)
{
	long double value;
	ASSERT_FALSE(StrToNumWrapper::TryStold(this->failStringTest, value));
}

TEST_F(CStrToNumWrapperTestFixture, TryStoldEmptyFail)
{
	long double value;
	ASSERT_FALSE(StrToNumWrapper::TryStold(this->emptyStringTest, value));
}
