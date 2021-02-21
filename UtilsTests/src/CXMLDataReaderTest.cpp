#include <gtest/gtest.h>

#include "CXMLDataReader.h"

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
