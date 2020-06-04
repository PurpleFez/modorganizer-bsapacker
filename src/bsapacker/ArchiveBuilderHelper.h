#ifndef ARCHIVEBUILDERHELPER_H
#define ARCHIVEBUILDERHELPER_H

#include "bsapacker_global.h"
#include <bsapacker/IArchiveBuilderHelper.h>
#include <bsapacker/ISettingsService.h>

#include <array>

namespace BsaPacker
{
	class BSAPACKER_EXPORT ArchiveBuilderHelper : public IArchiveBuilderHelper
	{
	public:
		ArchiveBuilderHelper(const ISettingsService* settingsService);
		[[nodiscard]] bool isFileIgnorable(const std::filesystem::path&, const std::vector<std::string>&) const override;
		[[nodiscard]] bool isIncompressible(const std::filesystem::path&) const override;
		[[nodiscard]] bool isExtensionBlacklisted(const std::filesystem::path&) const override;
		[[nodiscard]] uint32_t getFileCount(const std::filesystem::path&) const override;
		[[nodiscard]] std::vector<std::string> getRootDirectoryFilenames(const std::filesystem::path&) const override;
		[[nodiscard]] bool doesPathContainFiles(const std::filesystem::path&, const std::vector<std::string>&) const override;

		const static std::array <std::string, 3> INCOMPRESSIBLE_TYPES;

	private:

		const ISettingsService* m_SettingsService = nullptr;
	};
} // namespace BsaPacker

#endif // ARCHIVEBUILDERHELPER_H
