#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ArchiveNameService.h"
#include "MockModContext.h"

using namespace BsaPacker;
using ::testing::NaggyMock;

namespace BsaPackerTests
{
	class ArchiveNameServiceFacts : public ::testing::Test
	{
	protected:
		void SetUp() override {
			naggyMockModContext = new NaggyMock<MockModContext>();
		}

		void TearDown() override {
			delete naggyMockModContext;
		}

		NaggyMock<MockModContext>* naggyMockModContext;
	};

	TEST_F(ArchiveNameServiceFacts, Ctor_Always_Constructs)
	{
		EXPECT_NO_THROW(
			auto result = ArchiveNameService(
				naggyMockModContext
			);
		);
	}
}