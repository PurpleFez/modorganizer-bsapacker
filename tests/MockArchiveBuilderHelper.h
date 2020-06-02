#include <bsapacker/IArchiveBuilderHelper.h>
#include <gmock/gmock.h>

using namespace BsaPacker;

class MockArchiveBuilderHelper : public IArchiveBuilderHelper
{
public:
	MOCK_METHOD(bool, isFileIgnorable, (const QString&, const QStringList&), (const, override));
	MOCK_METHOD(bool, isIncompressible, (const QString&), (const, override));
	MOCK_METHOD(bool, isExtensionBlacklisted, (const QString&), (const, override));
	MOCK_METHOD(uint32_t, getFileCount, (const QDir&), (const, override));
	MOCK_METHOD(QStringList, getRootDirectoryFilenames, (const QDir&), (const, override));
};