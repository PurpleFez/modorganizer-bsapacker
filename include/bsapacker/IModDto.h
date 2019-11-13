#ifndef IMODDTO_H
#define IMODDTO_H

#include <QString>

namespace BsaPacker
{
	class IModDto
	{
	public:
		virtual ~IModDto() = default;
		[[nodiscard]] virtual int NexusId() const = 0;
		[[nodiscard]] virtual QString ModName() const = 0;
		[[nodiscard]] virtual QString Path() const = 0;
		[[nodiscard]] virtual QString ArchiveName() const = 0;
		[[nodiscard]] virtual QString ArchiveExtension() const  = 0;
	};
} // namespace BsaPacker

#endif // IMODDTO_H
