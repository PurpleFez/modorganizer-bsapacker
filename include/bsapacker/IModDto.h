#ifndef IMODDTO_H
#define IMODDTO_H

#include <string>

namespace BsaPacker
{
	class IModDto
	{
	public:
		virtual ~IModDto() = default;
		[[nodiscard]] virtual std::string ArchiveExtension() const  = 0;
		[[nodiscard]] virtual std::string ArchiveName() const = 0;
		[[nodiscard]] virtual std::string Directory() const = 0;
		[[nodiscard]] virtual std::string ModForename() const = 0;
		[[nodiscard]] virtual int NexusId() const = 0;
	};
} // namespace BsaPacker

#endif // IMODDTO_H
