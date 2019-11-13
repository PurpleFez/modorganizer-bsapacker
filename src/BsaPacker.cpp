#include <BsaPacker.h>

#include <bsapacker/ArchiveAutoService.h>
#include <bsapacker/ArchiveBuildDirector.h>
#include <bsapacker/ArchiveBuilderHelper.h>
#include <bsapacker/ArchiveBuilderFactory.h>
#include "ArchiveExtensionService.h"
#include "DummyPluginLogic.h"
#include "DummyPluginServiceFactory.h"
#include "FileWriterService.h"
#include "HideLooseAssetService.h"
#include "ModContext.h"
#include "ModDto.h"
#include "SettingsService.h"
#include "WorkClass.h"
#include <bsapacker/ModDtoFactory.h>
#include <bsapacker/PackerProgressDialogFactory.h>
#include <QMessageBox>

#include <iostream>

#include <boost/di.hpp>


namespace BsaPacker
{
	bool Bsa_Packer::init(MOBase::IOrganizer* moInfo)
	{
		this->m_Organizer = moInfo;
		this->m_ModContext = std::make_unique<ModContext>(this->m_Organizer);
		this->m_SettingsService = std::make_unique<SettingsService>(this->m_Organizer);
		return true;
	}

	QString Bsa_Packer::name() const
	{
		return QStringLiteral("BSA Packer");
	}

	QString Bsa_Packer::author() const
	{
		return QStringLiteral("MattyFez");
	}

	QString Bsa_Packer::description() const
	{
		return tr("Transform loose files into a Bethesda Softworks Archive file (.bsa/.ba2).");
	}

	MOBase::VersionInfo Bsa_Packer::version() const
	{
		return MOBase::VersionInfo(1, 0, 0, MOBase::VersionInfo::RELEASE_FINAL);
	}

	bool Bsa_Packer::isActive() const
	{
		return this->m_SettingsService->GetPluginSetting(SettingsService::SETTING_ENABLED).toBool();
		//return true; //m_Organizer->pluginSetting(this->name(), SettingsService::SETTING_ENABLED).toBool();
	}

	QList<MOBase::PluginSetting> Bsa_Packer::settings() const
	{
		return SettingsService::PluginSettings;
		//return this->m_SettingsService->GetPluginSettings(); // reads this before settings IOrganizer
		/*
		return QList<MOBase::PluginSetting> {
			MOBase::PluginSetting(SettingsService::SETTING_HIDE_LOOSE_ASSETS, QObject::tr("After creating the archive, set loose assets to hidden."), false),
			MOBase::PluginSetting(SettingsService::SETTING_CREATE_PLUGINS, QObject::tr("Create a dummy plugin to load the archive if one does not exist."), false),
			MOBase::PluginSetting(SettingsService::SETTING_ENABLED, QObject::tr("Allow this plugin to run."), false),
			MOBase::PluginSetting(SettingsService::SETTING_BLACKLISTED_FILES, QObject::tr("Specify a semi-colon seperated list of file extensions to ignore when packing."), ".txt;.hkx;.xml;.ini")
			//MOBase::PluginSetting(SettingsService::SETTING_SPLIT_ARCHIVES, QObject::tr("Automatically create multiple archives if they exceed the size limit."), false);
		};
		*/
	}

	QString Bsa_Packer::tooltip() const
	{
		return tr("Transform loose files into a Bethesda Softworks Archive file (.bsa/.ba2).");
	}

	QIcon Bsa_Packer::icon() const
	{
		return QIcon();
	}

	QString Bsa_Packer::displayName() const
	{
		return tr("BSA Packer");
	}

	void Bsa_Packer::display() const
	{
		const auto injector = di::make_injector(
			di::bind<IModContext>.to(this->m_ModContext.get()),
			di::bind<ISettingsService>.to(this->m_SettingsService.get()),
			di::bind<IModDtoFactory>.to<ModDtoFactory>(),
			di::bind<IArchiveBuilderHelper>.to<ArchiveBuilderHelper>(),
			di::bind<IArchiveBuilderFactory>.to<ArchiveBuilderFactory>(),
			di::bind<IArchiveAutoService>.to<ArchiveAutoService>(),
			di::bind<IPackerProgressDialogFactory>.to<PackerProgressDialogFactory>(),
			di::bind<IDummyPluginServiceFactory>.to<DummyPluginServiceFactory>(),
			di::bind<IFileWriterService>.to<FileWriterService>(),
			di::bind<IArchiveExtensionService>.to<ArchiveExtensionService>(),
			di::bind<IDummyPluginLogic>.to<DummyPluginLogic>(),
			di::bind<IHideLooseAssetService>.to<HideLooseAssetService>()
			//di::bind<di::extension::ifactory<IModDto, int, QString, QString, QString>>().to(di::extension::factory<ModDto>{})
		);

		BsaPackerWorker worker = di::create<BsaPackerWorker>(injector);
		worker.DoWork();
	}

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
	Q_EXPORT_PLUGIN2(myTool, BSA_Packer)
#endif

} // namespace BsaPacker
