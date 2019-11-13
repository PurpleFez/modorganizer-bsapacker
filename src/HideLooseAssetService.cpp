#include "HideLooseAssetService.h"

#include <QDir>
#include <QString>
#include <QtConcurrent/QtConcurrentMap>

#include "SettingsService.h"

namespace BsaPacker
{
	HideLooseAssetService::HideLooseAssetService(const ISettingsService* settingsService)
		: m_SettingsService(settingsService)
	{
	}

	bool HideLooseAssetService::HideLooseAssets(const QDir& modDirectory) const
	{
		if (!this->m_SettingsService->GetPluginSetting(SettingsService::SETTING_HIDE_LOOSE_ASSETS).toBool()) {
			return false;
		}

		const QString& absModDir = modDirectory.absolutePath();
		for (const QString& subDir : modDirectory.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
			const QString& absPath = absModDir + '/' + subDir;
			QDir dir(absPath);
			if (!dir.dirName().endsWith(".mohidden")) {
				dir.rename(absPath, absPath + ".mohidden");
			}
		}
		return true;

		/*
		const std::function<void(const QString&)> hideFolder = [&](const QString& subDir)
		{
			const QString& absPath = absModDir + '/' + subDir;
			QDir dir(absPath);
			if (!dir.dirName().endsWith(".mohidden"))
				dir.rename(absPath, absPath + ".mohidden");
		};
		*/
		//QtConcurrent::blockingMap(modDirectory.entryList(QDir::Dirs | QDir::NoDotAndDotDot), hideFolder);
	}
}
