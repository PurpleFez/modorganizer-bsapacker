#include <bsapacker/GeneralArchiveBuilder.h>

#include <bsapacker/ArchiveBuilderHelper.h>
#include <QDirIterator>
#include <QApplication>

namespace BsaPacker
{
	GeneralArchiveBuilder::GeneralArchiveBuilder(const IArchiveBuilderHelper* archiveBuilderHelper, const QDir& rootDir, const bsa_archive_type_t type)
		: m_ArchiveBuilderHelper(archiveBuilderHelper), m_RootDirectory(rootDir)
	{
		this->m_Cancelled = false;
		this->m_Archive = std::make_unique<QBSArchiveAuto>(type);
		this->m_RootDirectory.setFilter(QDir::Files | QDir::NoDotAndDotDot);
	}

	uint32_t GeneralArchiveBuilder::setFiles()
	{
		uint32_t incompressibleFiles = 0;
		uint32_t compressibleFiles = 0;
		int count = 0;
		const QStringList& rootDirFiles = this->m_ArchiveBuilderHelper->getRootDirectoryFilenames(this->m_RootDirectory);
		QDirIterator iterator(this->m_RootDirectory, QDirIterator::Subdirectories);
		while (iterator.hasNext()) {
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

			const std::string root = this->m_RootDirectory.absolutePath().toStdString() + '/';
			const std::string file = filepath.toStdString();
			const libbsarch::disk_blob blob(root, file);
			this->m_Archive->add_file_from_disk(blob);
		}
		this->m_Archive->set_compressed(!static_cast<bool>(incompressibleFiles));
		return incompressibleFiles + compressibleFiles;
	}

	void GeneralArchiveBuilder::setShareData(const bool value)
	{
		this->m_Archive->set_share_data(value);
	}

	std::unique_ptr<QBSArchiveAuto> GeneralArchiveBuilder::getArchive()
	{
		return std::move(this->m_Archive);
	}

	uint32_t GeneralArchiveBuilder::getFileCount() const
	{
		return this->m_ArchiveBuilderHelper->getFileCount(this->m_RootDirectory);
	}

	QString GeneralArchiveBuilder::getRootPath() const
	{
		return this->m_RootDirectory.path();
	}

	void GeneralArchiveBuilder::cancel()
	{
		this->m_Cancelled = true;
	}
} // namespace BsaPacker
