#include "NullModDto.h"

namespace BsaPacker
{
	std::string NullModDto::ArchiveExtension() const
	{
		return std::string();
	}

	std::string NullModDto::ArchiveName() const
	{
		return std::string();
	}

	std::string NullModDto::Directory() const
	{
		return std::string();
	}

	std::string NullModDto::ModForename() const
	{
		return std::string();
	}

	int NullModDto::NexusId() const
	{
		return 0;
	}
} // namespace BsaPacker
