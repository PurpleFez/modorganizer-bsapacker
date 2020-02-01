#ifndef IARCHIVENAMESERVICE_H
#define IARCHIVENAMESERVICE_H

#include <bsapacker/IModDto.h>
#include <bs_archive_auto.hpp>

namespace BsaPacker
{
	class IArchiveNameService
	{
	public:
		virtual ~IArchiveNameService() = default;
		virtual QString GetFileExtension() const = 0;
		virtual QString GetArchiveFullPath(bsa_archive_type_t, const IModDto*) const = 0;
	};
} // namespace BsaPacker

#endif // !IARCHIVENAMESERVICE_H
