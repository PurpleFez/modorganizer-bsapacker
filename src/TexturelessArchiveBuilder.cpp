#include <bsapacker/TexturelessArchiveBuilder.h>

#include <bsapacker/ArchiveBuilderHelper.h>
#include <QDirIterator>
#include <QApplication>

namespace BsaPacker
{
	TexturelessArchiveBuilder::TexturelessArchiveBuilder(const IArchiveBuilderHelper* archiveBuilderHelper, const QDir& rootDir, const bsa_archive_type_t type)
		: m_ArchiveBuilderHelper(archiveBuilderHelper), m_RootDirectory(rootDir)
	{
		this->m_Cancelled = false;
		this->m_Archive = std::make_unique<libbsarch::bs_archive_auto>(type);
		this->m_RootDirectory.setFilter(QDir::Files | QDir::NoDotAndDotDot);
	}

	uint32_t TexturelessArchiveBuilder::setFiles()
	{
		uint32_t incompressibleFiles = 0;
		uint32_t compressibleFiles = 0;
		int count = 0;
		const QStringList& rootDirFilenames = this->m_ArchiveBuilderHelper->getRootDirectoryFilenames(this->m_RootDirectory);
		QDirIterator iterator(this->m_RootDirectory, QDirIterator::Subdirectories);
		while (iterator.hasNext()) {
			if (this->m_Cancelled) {
				this->m_Archive.reset();
				return 0;
			}

			const QString& filepath = iterator.next();
			const bool ignored = this->m_ArchiveBuilderHelper->isFileIgnorable(filepath, rootDirFilenames);

			Q_EMIT this->valueChanged(++count);
			if (ignored || filepath.endsWith(".dds", Qt::CaseInsensitive)) {
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

	void TexturelessArchiveBuilder::setShareData(const bool value)
	{
		this->m_Archive->set_share_data(value);
	}

	std::unique_ptr<libbsarch::bs_archive_auto> TexturelessArchiveBuilder::getArchive()
	{
		return std::move(this->m_Archive);
	}

	uint32_t TexturelessArchiveBuilder::getFileCount() const
	{
		return this->m_RootDirectory.count();
	}

	QString TexturelessArchiveBuilder::getRootPath() const
	{
		return this->m_RootDirectory.path();
	}

	void TexturelessArchiveBuilder::cancel()
	{
		this->m_Cancelled = true;
	}
} // namespace BsaPacker
