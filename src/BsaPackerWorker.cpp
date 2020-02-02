#include "BsaPackerWorker.h"

#include <QMessageBox>
#include <QProgressDialog>
#include <QFutureWatcher>
#include <QFuture>
#include <QtConcurrent/qtconcurrentrun.h>

#include <bsapacker/ArchiveBuildDirector.h>
#include <bsapacker/ModDtoFactory.h>

namespace BsaPacker
{
	BsaPackerWorker::BsaPackerWorker(
		const ISettingsService* settingsService,
		const IModDtoFactory* modDtoFactory,
		const IArchiveBuilderFactory* archiveBuilderFactory,
		const IArchiveAutoService* archiveAutoService,
		const IDummyPluginServiceFactory* dummyPluginServiceFactory,
		const IHideLooseAssetService* hideLooseAssetService,
		const IArchiveNameService* archiveNameService) :
		m_SettingsService(settingsService),
		m_ModDtoFactory(modDtoFactory),
		m_ArchiveBuilderFactory(archiveBuilderFactory),
		m_ArchiveAutoService(archiveAutoService),
		m_DummyPluginServiceFactory(dummyPluginServiceFactory),
		m_HideLooseAssetService(hideLooseAssetService),
		m_ArchiveNameService(archiveNameService)
	{
	}

	void BsaPackerWorker::DoWork() const
	{
		const std::unique_ptr<IModDto> modDto = this->m_ModDtoFactory->Create(); // does GUI stuff
		const std::vector<bsa_archive_type_e> types = this->m_ArchiveBuilderFactory->GetArchiveTypes(modDto.get());
		for (auto&& type : types) {
			const std::unique_ptr<IArchiveBuilder> builder = this->m_ArchiveBuilderFactory->Create(type, modDto.get());
			ArchiveBuildDirector director(builder.get());
			if (!director.Construct()) { // must check if cancelled, does GUI stuff
				continue;
			}
			const std::unique_ptr<libbsarch::bs_archive_auto> archive = builder->getArchive();
			if (archive) {
				const QString& archiveFullPath = this->m_ArchiveNameService->GetArchiveFullPath(type, modDto.get());
				this->BuildArchive(archive.get(), archiveFullPath);
			}
		}
		const std::unique_ptr<IDummyPluginService> pluginService = this->m_DummyPluginServiceFactory->Create();
		pluginService->CreatePlugin(modDto->Directory(), modDto->ArchiveName());

		if (!modDto->Directory().isEmpty()) {
			this->m_HideLooseAssetService->HideLooseAssets(modDto->Directory());
		}
	}

	void BsaPackerWorker::BuildArchive(libbsarch::bs_archive_auto* archive, const QString& archiveFullPath) const
	{
		QProgressDialog dialog("Building archive", "Cancel", 0, 0);
		QFutureWatcher<void> futureWatcher;
		QObject::connect(&futureWatcher, &QFutureWatcher<void>::finished, &dialog, &QProgressDialog::reset);
		QObject::connect(&dialog, &QProgressDialog::canceled, &futureWatcher, &QFutureWatcher<void>::cancel);
		QObject::connect(&futureWatcher,  &QFutureWatcher<void>::progressRangeChanged, &dialog, &QProgressDialog::setRange);
		QObject::connect(&futureWatcher, &QFutureWatcher<void>::progressValueChanged,  &dialog, &QProgressDialog::setValue);
		QFuture<void> future = QtConcurrent::run(this->m_ArchiveAutoService, &IArchiveAutoService::CreateBSA, archive, archiveFullPath);
		futureWatcher.setFuture(future);
		dialog.exec();
		future.waitForFinished();
		QMessageBox::information(nullptr, "", QObject::tr("Created") + " \"" + archiveFullPath + "\"");
	}
}
