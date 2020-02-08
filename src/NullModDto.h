#ifndef NULLMODDTO_H
#define NULLMODDTO_H

#include <bsapacker/IModDto.h>
#include <string>

namespace BsaPacker
{
	class NullModDto : public IModDto
	{
	public:
		[[nodiscard]] std::string ArchiveExtension() const override;
		[[nodiscard]] std::string ArchiveName() const override;
		[[nodiscard]] std::string Directory() const override;
		[[nodiscard]] std::string ModForename() const override;
		[[nodiscard]] int NexusId() const override;
	};
} // namespace BsaPacker

#endif // NULLMODDTO_H
