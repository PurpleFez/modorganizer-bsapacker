#include "NullModDto.h"

namespace BsaPacker
{
	QString NullModDto::AbsolutePath() const
	{
		return QString();
	}

	QString NullModDto::ArchiveExtension() const
	{
		return QString();
	}

	QString NullModDto::ArchiveName() const
	{
		return QString();
	}

	QString NullModDto::Directory() const
	{
		return QString();
	}

	QString BsaPacker::NullModDto::ModName() const
	{
		return QString();
	}

	int NullModDto::NexusId() const
	{
		return 0;
	}
} // namespace BsaPacker

