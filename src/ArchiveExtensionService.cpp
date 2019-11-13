#include "ArchiveExtensionService.h"

#include "NexusId.h"

namespace BsaPacker
{
	ArchiveExtensionService::ArchiveExtensionService(const IModContext* modContext)
		: m_ModContext(modContext)
	{
	}

	QString ArchiveExtensionService::GetFileExtension() const
	{
		switch (this->m_ModContext->GetNexusId()) {
			case NexusId::Morrowind:
			case NexusId::Oblivion:
			case NexusId::Fallout3:
			case NexusId::NewVegas:
			case NexusId::Skyrim:
			case NexusId::SkyrimSE:
				return QStringLiteral(".bsa");
			case NexusId::Fallout4:
				return QStringLiteral(".ba2");
			default:
				return QString();
		}
	}
}
