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
		virtual std::string GetFileExtension() const = 0;
		virtual std::string GetArchiveFullPath(bsa_archive_type_t, const IModDto*) const = 0;
		virtual std::string GetArchiveFullPathPartial(bsa_archive_type_t, const IModDto*) const = 0;
	};
} // namespace BsaPacker

#endif // !IARCHIVENAMESERVICE_H
