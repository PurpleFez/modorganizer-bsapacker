#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ModDtoFactory.h"

using namespace BsaPacker;
using ::testing::NaggyMock;

namespace BsaPackerTests
{
	class ModDtoFactoryFacts : public ::testing::Test
	{
	protected:
		void SetUp() override {
		}

		void TearDown() override {
		}
	};

	TEST_F(ModDtoFactoryFacts, Ctor_Always_Constructs)
	{
	}
}