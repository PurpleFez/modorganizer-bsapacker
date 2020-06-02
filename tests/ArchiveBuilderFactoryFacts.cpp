#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <bsapacker/ArchiveBuilderFactory.h>
#include "MockArchiveBuilderHelper.h"
#include "ModDto.h"
#include <bsapacker/NullArchiveBuilder.h>
#include <bsapacker/GeneralArchiveBuilder.h>
#include <bsapacker/TexturelessArchiveBuilder.h>
#include <bsapacker/TextureArchiveBuilder.h>
#include <typeindex>

using namespace BsaPacker;
using ::testing::NaggyMock;

namespace BsaPackerTests
{
	class ArchiveBuilderFactoryFacts : public ::testing::Test
	{
	protected:
		void SetUp() override {
			naggyMockArchiveBuilderHelper = new NaggyMock<MockArchiveBuilderHelper>();
		}

		void TearDown() override {
			delete naggyMockArchiveBuilderHelper;
		}

		NaggyMock<MockArchiveBuilderHelper>* naggyMockArchiveBuilderHelper;
	};

	TEST_F(ArchiveBuilderFactoryFacts, Ctor_Always_Constructs)
	{
		EXPECT_NO_THROW(
			auto sut = ArchiveBuilderFactory(naggyMockArchiveBuilderHelper);
		);
	}

	TEST_F(ArchiveBuilderFactoryFacts, Create_WhenArchiveTypeNone_ReturnsNullArchiveBuilder)
	{
		// Arrange
		auto sut = ArchiveBuilderFactory(naggyMockArchiveBuilderHelper);
		auto type = bsa_archive_type_e::baNone;

		// Act
		auto returned = sut.Create(type, nullptr);
		auto result = returned.get();

		// Assert
		auto resultType = dynamic_cast<NullArchiveBuilder*>(result);
		EXPECT_STREQ(typeid(NullArchiveBuilder).name(), typeid(*resultType).name());
	}

	TEST_F(ArchiveBuilderFactoryFacts, Create_WhenArchiveTypeTES3_ReturnsGeneralArchiveBuilder)
	{
		// Arrange
		auto sut = ArchiveBuilderFactory(naggyMockArchiveBuilderHelper);
		auto type = bsa_archive_type_e::baTES3;

		// Act
		auto returned = sut.Create(type, &ModDto(0, "", "", ""));
		auto result = returned.get();

		// Assert
		auto resultType = dynamic_cast<GeneralArchiveBuilder*>(result);
		EXPECT_STREQ(typeid(GeneralArchiveBuilder).name(), typeid(*resultType).name());
	}

		TEST_F(ArchiveBuilderFactoryFacts, Create_WhenArchiveTypeTES4_ReturnsGeneralArchiveBuilder)
	{
		// Arrange
		auto sut = ArchiveBuilderFactory(naggyMockArchiveBuilderHelper);
		auto type = bsa_archive_type_e::baTES4;

		// Act
		auto returned = sut.Create(type, &ModDto(0, "", "", ""));
		auto result = returned.get();

		// Assert
		auto resultType = dynamic_cast<GeneralArchiveBuilder*>(result);
		EXPECT_STREQ(typeid(GeneralArchiveBuilder).name(), typeid(*resultType).name());
	}
}
