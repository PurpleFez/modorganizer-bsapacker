#include "DummyPluginLogic.h"

#include <QFileInfo>
#include "SettingsService.h"

namespace BsaPacker
{
	DummyPluginLogic::DummyPluginLogic(
			const ISettingsService* settingsService,
			const IArchiveNameService* archiveNameService)
		: m_SettingsService(settingsService),
		  m_ArchiveNameService(archiveNameService)
	{
	}

	bool DummyPluginLogic::canCreateDummyESP(const std::string& fileNameNoExtension) const
	{
		const std::array<std::string, 2>& fileList = {
			fileNameNoExtension + ".esm",
			fileNameNoExtension + ".esp"
		};
		return this->canCreateDummy(fileList, fileNameNoExtension);
	}

	bool DummyPluginLogic::canCreateDummyESL(const std::string& fileNameNoExtension) const
	{
		const std::array<std::string, 3>& fileList = {
			fileNameNoExtension + ".esm",
			fileNameNoExtension + ".esp",
			fileNameNoExtension + ".esl"
		};
		return this->canCreateDummy(fileList, fileNameNoExtension);
	}

	template<std::size_t SIZE>
	bool DummyPluginLogic::canCreateDummy(const std::array<std::string, SIZE>& fileList, const std::string& fileNameNoExtension) const
	{
		const QFileInfo& archive(QString::fromStdString(fileNameNoExtension + this->m_ArchiveNameService->GetFileExtension()));
		if (!(archive.exists() && archive.isFile())) {
			return false;
		}

		if (!this->m_SettingsService->GetPluginSetting(SettingsService::SETTING_CREATE_PLUGINS).toBool()) {
			return false;
		}

		for (const std::string& filePath : fileList) {
			const QFileInfo fileInfo(QString::fromStdString(filePath));
			if (fileInfo.exists() && fileInfo.isFile()) {
				return false;
			}
		}
		return true;
	}
}
