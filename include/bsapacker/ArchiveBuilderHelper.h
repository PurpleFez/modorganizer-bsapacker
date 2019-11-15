#ifndef ARCHIVEBUILDERHELPER_H
#define ARCHIVEBUILDERHELPER_H

#include <bsapacker/IArchiveBuilderHelper.h>
#include <bsapacker/ISettingsService.h>
#include <qlibbsarch/BSArchiveAuto.h>

#include <array>
#include <cstdint>
#include <QDir>
#include <QObject>
#include <QProgressBar>
#include <QString>
#include <QStringList>

namespace BsaPacker
{
	class ArchiveBuilderHelper : public IArchiveBuilderHelper
	{
	public:
		ArchiveBuilderHelper(const ISettingsService* settingsService);
		~ArchiveBuilderHelper() override = default;
		[[nodiscard]] bool isFileIgnorable(const QString&, const QStringList&) const override;
		[[nodiscard]] bool isIncompressible(const QString&) const override;
		[[nodiscard]] bool isExtensionBlacklisted(const QString&) const override;
		[[nodiscard]] uint32_t getFileCount(const QDir&) const override;
		[[nodiscard]] QStringList getRootDirectoryFilenames(const QDir&) const override;

		const static std::array <QString, 3> INCOMPRESSIBLE_TYPES;

	private:
		const ISettingsService* m_SettingsService = nullptr;
	};
} // namespace BsaPacker

#endif // ARCHIVEBUILDERHELPER_H
