#ifndef IARCHIVEBUILDERHELPER_H
#define IARCHIVEBUILDERHELPER_H

#include <string>
#include <filesystem>
#include <vector>
#include <cstdint>

namespace BsaPacker
{
	class IArchiveBuilderHelper
	{
	public:
		virtual ~IArchiveBuilderHelper() = default;
		[[nodiscard]] virtual bool isFileIgnorable(const std::filesystem::path&, const std::vector<std::string>&) const = 0;
		[[nodiscard]] virtual bool isIncompressible(const std::filesystem::path&) const = 0;
		[[nodiscard]] virtual bool isExtensionBlacklisted(const std::filesystem::path&) const = 0;
		[[nodiscard]] virtual uint32_t getFileCount(const std::filesystem::path&) const = 0;
		[[nodiscard]] virtual std::vector<std::string> getRootDirectoryFilenames(const std::filesystem::path&) const = 0;
		[[nodiscard]] virtual bool doesPathContainFiles(const std::filesystem::path&, const std::vector<std::string>&) const = 0;
	};
} // namespace BsaPacker

#endif // IARCHIVEBUILDERHELPER_H
