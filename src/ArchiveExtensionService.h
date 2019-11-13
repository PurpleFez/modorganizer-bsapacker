#ifndef ARCHIVEEXTENSIONSERVICE_H
#define ARCHIVEEXTENSIONSERVICE_H

#include <bsapacker/IArchiveExtensionService.h>
#include <bsapacker/IModContext.h>

namespace BsaPacker
{
	class ArchiveExtensionService : public IArchiveExtensionService
	{
	public:
		ArchiveExtensionService(const IModContext* modContext);
		~ArchiveExtensionService() override = default;
		QString GetFileExtension() const override;

	private:
		const IModContext* m_ModContext = nullptr;
	};
}

#endif // ARCHIVEEXTENSIONSERVICE_H
