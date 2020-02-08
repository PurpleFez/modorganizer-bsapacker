#include <bsapacker/ArchiveBuilderHelper.h>

#include <QDirIterator>
#include <QtConcurrent/QtConcurrentMap>

#include "SettingsService.h"

namespace BsaPacker
{
	const std::array <QString, 3> ArchiveBuilderHelper::INCOMPRESSIBLE_TYPES = { "wav", "ogg", "mp3" };

	ArchiveBuilderHelper::ArchiveBuilderHelper(const ISettingsService* settingsService)
		: m_SettingsService(settingsService)
	{
	}

	uint32_t ArchiveBuilderHelper::getFileCount(const QDir& rootDirectory) const
	{
		QDirIterator it(rootDirectory, QDirIterator::Subdirectories);
		uint32_t count = 0;
		while (it.hasNext()) {
			it.next();
			count++;
		}
		return count;
	}

	QStringList ArchiveBuilderHelper::getRootDirectoryFilenames(const QDir& rootDirectory) const
	{
		const std::function<QString(const QFileInfo&)> getFilename = [](const QFileInfo& fi) {
			return fi.fileName();
		};
		return QtConcurrent::blockingMapped(rootDirectory.entryInfoList(QDir::Files),
											getFilename);
	}

	bool ArchiveBuilderHelper::isFileIgnorable(const QString& filepath, const QStringList& rootDirFilenames) const
	{
		const QFileInfo& fileInfo(filepath);
		const QString& filename = fileInfo.fileName();
		return rootDirFilenames.contains(filename) || // ignore files within mod directory
			fileInfo.isDir() || // ignore directories
			filename == "." || filename == ".." || // ignore current dir and parent dir entries
			ArchiveBuilderHelper::isExtensionBlacklisted(filename); // ignore user blacklisted file types
	}

	bool ArchiveBuilderHelper::isIncompressible(const QString& filename) const
	{
		for (const QString& str : ArchiveBuilderHelper::INCOMPRESSIBLE_TYPES) {
			if (filename.endsWith(str, Qt::CaseInsensitive)) {
				return true;
			}
		}
		return false;
	}

	bool ArchiveBuilderHelper::isExtensionBlacklisted(const QString& filename) const
	{
		const QStringList& blacklist = this->m_SettingsService->GetPluginSetting(SettingsService::SETTING_BLACKLISTED_FILES).toString().split(';');
		for (const QString& ext : blacklist) {
			if (filename.endsWith(ext, Qt::CaseInsensitive)) {
				return true;
			}
		}
		return false;
	}
} // namespace BsaPacker
