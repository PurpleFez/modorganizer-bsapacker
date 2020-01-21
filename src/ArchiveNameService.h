#ifndef ARCHIVENAMESERVICE_H
#define ARCHIVENAMESERVICE_H

#include <bsapacker/IArchiveNameService.h>
#include <bsapacker/IArchiveExtensionService.h>

namespace BsaPacker
{
	class ArchiveNameService : public IArchiveNameService
	{
	public:
		ArchiveNameService(const IArchiveExtensionService* archiveExtensionService);
		~ArchiveNameService() override = default;
		QString GetArchiveFullPath(bsa_archive_type_e type, const IModDto* modDto) const override;
	private:
		const IArchiveExtensionService* m_ArchiveExtensionService = nullptr;

		QString Infix(bsa_archive_type_e type) const;
	};
}

#endif // ARCHIVENAMESERVICE_H
