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

	int ModDto::NexusId() const
	{
		return this->m_NexusId;
	}

	QString ModDto::ModName() const
	{
		return this->m_Path.dirName();
	}

	QString ModDto::Path() const
	{
		return this->m_Path.path();
	}

	QString ModDto::ArchiveName() const
	{
		return this->m_Path.path() + '/' + this->m_ArchiveName;
	}

	QString ModDto::ArchiveExtension() const
	{
		return this->m_ArchiveExtension;
	}
} // namespace BsaPacker
