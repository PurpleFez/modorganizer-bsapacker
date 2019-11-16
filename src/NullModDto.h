#ifndef NULLMODDTO_H
#define NULLMODDTO_H

#include <bsapacker/IModDto.h>
#include <QString>

namespace BsaPacker
{
	class NullModDto : public IModDto
	{
	public:
		[[nodiscard]] QString AbsolutePath() const override;
		[[nodiscard]] QString ArchiveExtension() const override;
		[[nodiscard]] QString ArchiveName() const override;
		[[nodiscard]] QString Directory() const override;
		[[nodiscard]] QString ModName() const override;
		[[nodiscard]] int NexusId() const override;
	};
} // namespace BsaPacker

#endif // NULLMODDTO_H
