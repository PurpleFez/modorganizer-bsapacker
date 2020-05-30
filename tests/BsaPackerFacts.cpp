#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "BsaPacker.h"
#include "MockOrganizer.h"

using namespace BsaPacker;
using ::testing::NaggyMock;
using ::testing::Return;
using ::testing::Eq;

namespace BsaPackerTests
{
	class BsaPackerFacts : public ::testing::Test
	{
	protected:
		void SetUp() override {
		}

		void TearDown() override {
		}
	};

	TEST_F(BsaPackerFacts, CtorAndInit_Always_Constructs)
	{
		auto naggyMockOrganizer = NaggyMock<MockOrganizer>();

		auto result = Bsa_Packer();
		EXPECT_NO_THROW(result.init(&naggyMockOrganizer));
	}

	TEST_F(BsaPackerFacts, IsActive_WhenPluginEnabled_ReturnsTrue)
	{
		// Arrange
		Bsa_Packer sut;
		auto naggyMockOrganizer = NaggyMock<MockOrganizer>();
		ON_CALL(naggyMockOrganizer, pluginSetting(Eq("BSA Packer"), Eq(QStringLiteral("enabled"))))
			.WillByDefault(Return(true));
		sut.init(&naggyMockOrganizer);

		// Act
		auto result = sut.isActive();

		// Assert
		EXPECT_TRUE(result);
	}

	TEST_F(BsaPackerFacts, IsActive_WhenPluginDisabled_ReturnsFalse)
	{
		// Arrange
		Bsa_Packer sut;
		auto naggyMockOrganizer = NaggyMock<MockOrganizer>();
		ON_CALL(naggyMockOrganizer, pluginSetting(Eq("BSA Packer"), Eq("enabled")))
			.WillByDefault(Return(false));
		sut.init(&naggyMockOrganizer);

		// Act
		auto result = sut.isActive();

		// Assert
		EXPECT_FALSE(result);
	}
}
