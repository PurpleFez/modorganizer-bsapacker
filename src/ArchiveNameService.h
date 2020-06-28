#ifndef ARCHIVENAMESERVICE_H
#define ARCHIVENAMESERVICE_H

#include "bsapacker_global.h"
#include <bsapacker/IArchiveNameService.h>
#include <bsapacker/IModContext.h>

namespace BsaPacker
{
	class BSAPACKER_EXPORT ArchiveNameService : public IArchiveNameService
	{
	public:
		ArchiveNameService(const IModContext* modContext);
		~ArchiveNameService() override = default;
		std::string GetFileExtension() const override;
		std::string GetArchiveFullPath(bsa_archive_type_t type, const IModDto* modDto) const override;
		std::string GetArchiveFullPathPartial(bsa_archive_type_t type, const IModDto* modDto) const override;
	private:
		const IModContext* m_ModContext = nullptr;

		std::string Infix(bsa_archive_type_t type) const;
	};
}

#endif // ARCHIVENAMESERVICE_H
