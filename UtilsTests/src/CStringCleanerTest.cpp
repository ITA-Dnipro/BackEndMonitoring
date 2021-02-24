#include <gtest/gtest.h>

#include "CStringCleaner.h"

struct CStringCleanerTestFixture : public testing::Test
{
public:
	CStringCleanerTestFixture() = default;

	~CStringCleanerTestFixture() override = default;

	std::string testStr = "\n\t\n  \t\n TestString";
	std::string lowerStr = "\n\t\n  \t\n teststring";
	std::string trimmedStr = "TestString";
	std::string trimmedLowerStr = "teststring";
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
