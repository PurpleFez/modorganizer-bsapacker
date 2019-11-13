#include "NullModDto.h"

namespace BsaPacker
{
	int NullModDto::NexusId() const
	{
		return 0;
	}

	QString BsaPacker::NullModDto::ModName() const
	{
		return QString();
	}

	QString NullModDto::Path() const
	{
		return QString();
	}

	QString NullModDto::ArchiveName() const
	{
		return QString();
	}

	QString NullModDto::ArchiveExtension() const
	{
		return QString();
	}
} // namespace BsaPacker
