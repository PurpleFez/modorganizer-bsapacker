#include "ArchiveNameService.h"

namespace BsaPacker
{
	ArchiveNameService::ArchiveNameService(const IArchiveExtensionService* archiveExtensionService)
		: m_ArchiveExtensionService(archiveExtensionService)
	{
	}

	QString ArchiveNameService::GetArchiveName(bsa_archive_type_e type, const IModDto* modDto) const
	{
		return modDto->ModName() + this->Infix(type) + this->m_ArchiveExtensionService->GetFileExtension();
	}

	QString ArchiveNameService::Infix(bsa_archive_type_e type) const
	{
		switch (type) {
		case baFO4:
			return QStringLiteral(" - Main");
		case baFO4dds:
			return QStringLiteral(" - Textures");
		case baTES3:
		case baTES4:
		case baFO3:
		case baSSE:
		case baNone:
		default:
			return QString();
		};
	}
}