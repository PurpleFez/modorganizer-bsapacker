#include <bsapacker/ArchiveBuilderHelper.h>

#include <algorithm>
#include <boost/algorithm/string.hpp>

#include "SettingsService.h"

using std::filesystem::path;
using std::filesystem::directory_entry;
using std::filesystem::directory_iterator;
using std::filesystem::recursive_directory_iterator;

namespace BsaPacker
{
	const std::array <std::string, 3> ArchiveBuilderHelper::INCOMPRESSIBLE_TYPES = { ".wav", ".ogg", ".mp3" };

	ArchiveBuilderHelper::ArchiveBuilderHelper(const ISettingsService* settingsService)
		: m_SettingsService(settingsService)
	{
	}
	uint32_t ArchiveBuilderHelper::getFileCount(const path& rootDirectory) const
	{
		uint32_t count = 0;
		for(auto& p : recursive_directory_iterator(rootDirectory)) {
			count++;
		}
		return count;
	}

	std::vector<std::string> ArchiveBuilderHelper::getRootDirectoryFilenames(const path& rootDirectory) const
	{
		std::vector<std::string> filenames;
		for (const auto& entry : directory_iterator(rootDirectory)) {
			const auto& path = entry.path().filename().generic_string();
			filenames.push_back(path);
		}
		return filenames;
	}

	bool ArchiveBuilderHelper::isFileIgnorable(const path& filepath, const std::vector<std::string>& rootDirFilenames) const
	{
		const auto& filename = filepath.filename();
		return this->doesPathContainFiles(filepath, rootDirFilenames) || // ignore files within mod directory
			directory_entry(filepath).is_directory() || // ignore directories
			filename == "." || filename == ".." || // ignore current dir and parent dir entries
			this->isExtensionBlacklisted(filename); // ignore user blacklisted file types
	}

	bool ArchiveBuilderHelper::isIncompressible(const path& filename) const
	{
		for (const auto& ext : ArchiveBuilderHelper::INCOMPRESSIBLE_TYPES) {
			if (boost::iequals(filename.extension().generic_string(), ext)) {
				return true;
			}
		}
		return false;
	}

	bool ArchiveBuilderHelper::isExtensionBlacklisted(const path& filename) const
	{
		const auto& setting = this->m_SettingsService->GetPluginSetting(SettingsService::SETTING_BLACKLISTED_FILES).toString().toStdString();
		std::vector<std::string> blacklist;
		boost::split(blacklist, setting, [](char c){return c == ';';});
		for (const auto& ext : blacklist) {
			if (boost::iequals(filename.extension().generic_string(), ext)) {
				return true;
			}
		}
		return false;
	}

	bool ArchiveBuilderHelper::doesPathContainFiles(const path& filepath, const std::vector<std::string>& files) const
	{
		return std::find(files.begin(), files.end(), filepath) != files.end();
	}
} // namespace BsaPacker
