#ifndef NULLMODDTO_H
#define NULLMODDTO_H

#include <bsapacker/IModDto.h>
#include <QString>

namespace BsaPacker
{
	class NullModDto : public IModDto
	{
	public:
		// IModContext interface
		[[nodiscard]] int NexusId() const override;
		[[nodiscard]] QString ModName() const override;
		[[nodiscard]] QString Path() const override;
		[[nodiscard]] QString ArchiveName() const override;
		[[nodiscard]] QString ArchiveExtension() const override;
	};
} // namespace BsaPacker

#endif // NULLMODDTO_H
