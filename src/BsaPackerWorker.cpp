#include "BsaPackerWorker.h"

#include <QtGlobal>

#include <QMessageBox>
#include <QProgressDialog>
#include <QFutureWatcher>
#include <QFuture>
#include <QFileInfo>
#include <QtConcurrent/qtconcurrentrun.h>

#include <bsapacker/ArchiveBuildDirector.h>
#include <bsapacker/ModDtoFactory.h>

#include <cstdio>
#include <sys/stat.h>

namespace BsaPacker
{
	const QString INCOMPLETE_EXTENSION = ".part";
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
		int built = 0;
		for (auto&& type : types) {
			const std::unique_ptr<IArchiveBuilder> builder = this->m_ArchiveBuilderFactory->Create(type, modDto.get());
			ArchiveBuildDirector director(this->m_SettingsService, builder.get());
			director.Construct(); // must check if cancelled
			const std::unique_ptr<libbsarch::bs_archive_auto> archive = builder->getArchive();
			if (archive) {

				built += this->BuildArchive(archive.get(), type, modDto.get()) ? 1 : 0;
			}
		}
		if (built > 0) {
			const std::unique_ptr<IDummyPluginService> pluginService = this->m_DummyPluginServiceFactory->Create();
			pluginService->CreatePlugin(modDto->Directory(), modDto->ArchiveName());

			if (!modDto->Directory().empty()) {
				this->m_HideLooseAssetService->HideLooseAssets(modDto->Directory());
			}
		}
	}

	bool BsaPackerWorker::BuildArchive(QBSArchiveAuto* archive, const bsa_archive_type_t type, const IModDto* modDto) const
	{
		const std::string& archiveFullPathPartial = this->m_ArchiveNameService->GetArchiveFullPathPartial(type, modDto);
		bool cancelled = false;
		QProgressDialog dialog("Building archive", "Cancel", 0, 0);
		QFutureWatcher<void> futureWatcher;
		QObject::connect(&futureWatcher, &QFutureWatcher<void>::finished, &dialog, &QProgressDialog::reset);
		QObject::connect(&dialog, &QProgressDialog::canceled, archive, &QBSArchiveAuto::cancel);
		QObject::connect(&dialog, &QProgressDialog::canceled, [&]() {
			cancelled = true;
		});
		QObject::connect(&futureWatcher,  &QFutureWatcher<void>::progressRangeChanged, &dialog, &QProgressDialog::setRange);
		QObject::connect(&futureWatcher, &QFutureWatcher<void>::progressValueChanged,  &dialog, &QProgressDialog::setValue);
		QFuture<void> future = QtConcurrent::run(this->m_ArchiveAutoService, &IArchiveAutoService::CreateBSA, archive, archiveFullPathPartial);
		futureWatcher.setFuture(future);
		dialog.exec();
		future.waitForFinished();
		if (cancelled) {
			return false;
		}
		const std::string& archiveFullPath = this->m_ArchiveNameService->GetArchiveFullPath(type, modDto);
		struct stat buffer;
		if (stat(archiveFullPath.c_str(), &buffer)) {
			if(remove(archiveFullPath.c_str())) {
				qCritical() << "Error deleting file";
			} else {
				qInfo() << "File successfully deleted";
			}
		}
		if(rename(archiveFullPathPartial.c_str(), archiveFullPath.c_str())) {
			qCritical() << "Error renaming file";
		} else {
			qInfo() << "File successfully renamed";
		}
		QMessageBox::information(nullptr, "", QObject::tr("Created") + " \"" + QString::fromStdString(archiveFullPath) + "\"");
		return true;
	}
}
