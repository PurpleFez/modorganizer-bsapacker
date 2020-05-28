#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include "BsaPacker.h"
#include "MockOrganizer.h"

using namespace MOBase;
using namespace BsaPacker;
using ::testing::NiceMock;
using ::testing::NaggyMock;
using ::testing::StrictMock;
using ::testing::Return;
using ::testing::Eq;

TEST(BsaPackerFacts, IsActive_WhenPluginEnabled_ReturnsTrue)
{
	// Arrange
	Bsa_Packer sut;
	auto strictMockOrganizer = NaggyMock<MockOrganizer>();
	ON_CALL(strictMockOrganizer, pluginSetting(Eq("BSA Packer"), Eq(QStringLiteral("enabled"))))
		.WillByDefault(Return(true));
	sut.init(&strictMockOrganizer);

	// Act
	auto result = sut.isActive();

	// Assert
	EXPECT_TRUE(result);
}

TEST(BsaPackerFacts, IsActive_WhenPluginDisabled_ReturnsFalse)
{
	// Arrange
	Bsa_Packer sut;
	auto strictMockOrganizer = NaggyMock<MockOrganizer>();
	ON_CALL(strictMockOrganizer, pluginSetting(Eq("BSA Packer"), Eq("enabled")))
		.WillByDefault(Return(false));
	sut.init(&strictMockOrganizer);

	// Act
	auto result = sut.isActive();

	// Assert
	EXPECT_FALSE(result);
}

