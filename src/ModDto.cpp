#include "ModDto.h"

#include <QDir>

namespace BsaPacker
{
	ModDto::ModDto(
		const int nexusId,
		const QString& modDir,
		const QString& archiveName,
		const QString& archiveExtension)
		: m_NexusId(nexusId),
		  m_Path(modDir),
		  m_ArchiveName(archiveName),
		  m_ArchiveExtension(archiveExtension)
	{
	}

	std::string ModDto::ArchiveExtension() const
	{
		return this->m_ArchiveExtension.toStdString();
	}

	std::string ModDto::ArchiveName() const
	{
		return this->m_ArchiveName.toStdString();
	}

	std::string ModDto::Directory() const
	{
		return this->m_Path.path().toStdString();
	}

	std::string ModDto::ModForename() const
	{
		return this->m_Path.dirName().toStdString();
	}

	int ModDto::NexusId() const
	{
		return this->m_NexusId;
	}
} // namespace BsaPacker
