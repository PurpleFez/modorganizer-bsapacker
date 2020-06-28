#include "ArchiveNameService.h"

#include "NexusId.h"

namespace BsaPacker
{
	ArchiveNameService::ArchiveNameService(const IModContext* modContext)
		: m_ModContext(modContext)
	{
	}

	std::string ArchiveNameService::GetFileExtension() const
	{
		switch (this->m_ModContext->GetNexusId()) {
		case NexusId::Morrowind:
		case NexusId::Oblivion:
		case NexusId::Fallout3:
		case NexusId::NewVegas:
		case NexusId::Skyrim:
		case NexusId::SkyrimSE:
			return ".bsa";
		case NexusId::Fallout4:
			return ".ba2";
		default:
			return std::string();
		}
	}

	std::string ArchiveNameService::GetArchiveFullPath(const bsa_archive_type_t type, const IModDto* modDto) const
	{
		return modDto->Directory() + '/' + modDto->ArchiveName() + this->Infix(type) + this->GetFileExtension();
	}

	std::string ArchiveNameService::GetArchiveFullPathPartial(bsa_archive_type_t type, const IModDto* modDto) const
	{
		return modDto->Directory() + '/' + modDto->ModForename() + this->Infix(type) + this->GetFileExtension() + ".part";
	}

	std::string ArchiveNameService::Infix(const bsa_archive_type_t type) const
	{
		switch (type) {
		case baFO4:
			return " - Main";
		case baFO4dds:
			return " - Textures";
		case baTES3:
		case baTES4:
		case baFO3:
		case baSSE:
		case baNone:
		default:
			return std::string();
		};
	}
}