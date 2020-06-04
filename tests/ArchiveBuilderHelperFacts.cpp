#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <bsapacker/ArchiveBuilderHelper.h>
#include "MockSettingsService.h"

using namespace BsaPacker;
using std::filesystem::path;
using ::testing::NaggyMock;
using ::testing::Return;

namespace BsaPackerTests
{
	class ArchiveBuilderHelperFacts : public ::testing::Test
	{
	protected:
		void SetUp() override {
			naggyMockSettingsService = new NaggyMock<MockSettingsService>();
			naggyPath = new NaggyMock<path>();
		}

		void TearDown() override {
			delete naggyMockSettingsService;
			delete naggyPath;
		}

		NaggyMock<MockSettingsService>* naggyMockSettingsService;
		NaggyMock<std::filesystem::path>* naggyPath;
	};

	TEST_F(ArchiveBuilderHelperFacts, CtorAndInit_Always_Constructs)
	{
		EXPECT_NO_THROW(
			auto result = ArchiveBuilderHelper(naggyMockSettingsService);
		);
	}

	TEST_F(ArchiveBuilderHelperFacts, getFileCount_WhenEmptyDir_Returns0)
	{
		// Arrange
		auto sut = ArchiveBuilderHelper(naggyMockSettingsService);

		// Act
		auto result = sut.getFileCount(*naggyPath);

		// Assert
		FAIL();
	}
}