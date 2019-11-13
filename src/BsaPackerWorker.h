#ifndef BSAPACKERWORKER_H
#define BSAPACKERWORKER_H

#include <bsapacker/IArchiveAutoService.h>
#include <bsapacker/IArchiveBuilderFactory.h>
#include <bsapacker/IDummyPluginServiceFactory.h>
#include <bsapacker/IHideLooseAssetService.h>
#include <bsapacker/IModContext.h>
#include <bsapacker/IModDtoFactory.h>
#include <bsapacker/IPackerProgressDialogFactory.h>
#include <bsapacker/ISettingsService.h>

#include <boost/di/extension/injections/factory.hpp>

namespace di = boost::di;

namespace BsaPacker
{
	class BsaPackerWorker
	{
	public:
		//WorkClass(const di::extension::ifactory<IModDtoFactory>& modDtoFactory);
		BsaPackerWorker(
				const ISettingsService* settingsService,
				const IModDtoFactory* modDtoFactory,
				const IArchiveBuilderFactory* archiveBuilderFactory,
				const IArchiveAutoService* archiveAutoService,
				const IDummyPluginServiceFactory* dummyPluginService,
				const IHideLooseAssetService* hideLooseAssetService);
		void DoWork() const;

	private:
		//const di::extension::ifactory<IModDto>& m_ModDtoFactory;
		const ISettingsService* m_SettingsService = nullptr;
		const IModDtoFactory* m_ModDtoFactory = nullptr;
		const IArchiveBuilderFactory* m_ArchiveBuilderFactory = nullptr;
		const IArchiveAutoService* m_ArchiveAutoService = nullptr;
		const IDummyPluginServiceFactory* m_DummyPluginServiceFactory = nullptr;
		const IHideLooseAssetService* m_HideLooseAssetService = nullptr;
	};
}

#endif // BSAPACKERWORKER_H
