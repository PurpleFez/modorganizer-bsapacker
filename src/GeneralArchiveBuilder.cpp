#include <bsapacker/GeneralArchiveBuilder.h>

#include <bsapacker/ArchiveBuilderHelper.h>

#include <array>
#include <QDir>
#include <QDirIterator>
#include <QStringList>
#include <QtConcurrent/QtConcurrentMap>
#include <QApplication>
#include <QMessageBox>

namespace BsaPacker
{
	GeneralArchiveBuilder::GeneralArchiveBuilder(const IArchiveBuilderHelper* archiveBuilderHelper, const QDir& rootDir)
		: m_ArchiveBuilderHelper(archiveBuilderHelper), m_RootDirectory(rootDir)
	{
		this->m_Cancelled = false;
		this->m_Archive = std::make_unique<BSArchiveAuto>(this->m_RootDirectory.path());
	}

	uint32_t GeneralArchiveBuilder::setFiles()
	{
		uint32_t incompressibleFiles = 0;
		uint32_t compressibleFiles = 0;
		int count = 0;
		const QStringList& rootDirFiles = this->m_ArchiveBuilderHelper->getRootDirectoryFilenames(this->m_RootDirectory);
		QDirIterator iterator(this->m_RootDirectory, QDirIterator::Subdirectories);
		while (iterator.hasNext()) {
			QApplication::processEvents();

			if (this->m_Cancelled) {
				this->m_Archive.reset();
				return 0;
			}

			const QString& filepath = iterator.next();
			const bool ignored = this->m_ArchiveBuilderHelper->isFileIgnorable(filepath, rootDirFiles);

			Q_EMIT this->valueChanged(++count);
			if (ignored) {
				continue;
			}

			this->m_ArchiveBuilderHelper->isIncompressible(filepath) ? ++incompressibleFiles : ++compressibleFiles;
			this->m_Archive->addFileFromDiskRoot(filepath);
		}
		this->m_Archive->setCompressed(!static_cast<bool>(incompressibleFiles));
		return incompressibleFiles + compressibleFiles;
	}

	void GeneralArchiveBuilder::setShareData(const bool value)
	{
		this->m_Archive->setShareData(value);
	}

	std::unique_ptr<BSArchiveAuto> GeneralArchiveBuilder::getArchive()
	{
		return std::move(this->m_Archive);
	}

	uint32_t GeneralArchiveBuilder::getFileCount() const
	{
		return this->m_ArchiveBuilderHelper->getFileCount(this->m_RootDirectory);
	}

	void GeneralArchiveBuilder::cancel()
	{
		this->m_Cancelled = true;
	}
} // namespace BsaPacker
