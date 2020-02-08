#include <bsapacker/ArchiveBuildDirector.h>

#include <QtConcurrent/QtConcurrentRun>

#include <QDebug>

namespace BsaPacker
{
	ArchiveBuildDirector::ArchiveBuildDirector(
		IArchiveBuilder* archiveBuilder) :
		m_ArchiveBuilder(archiveBuilder),
		dialog("Finding and marking files for archival", "Cancel", 0, this->m_ArchiveBuilder->getFileCount())
	{
		QObject::connect(&futureWatcher, &QFutureWatcher<void>::finished, &dialog, &QProgressDialog::reset);
		QObject::connect(&dialog, &QProgressDialog::canceled, this->m_ArchiveBuilder, &IArchiveBuilder::cancel);
		QObject::connect(&futureWatcher,  &QFutureWatcher<void>::progressRangeChanged, &dialog, &QProgressDialog::setRange);
		QObject::connect(&futureWatcher, &QFutureWatcher<void>::progressValueChanged,  &dialog, &QProgressDialog::setValue);
	}

	uint32_t ArchiveBuildDirector::Construct()
	{
		qDebug() << this->m_ArchiveBuilder->getFileCount() << "files in directory";
		//QObject::connect(this->m_ArchiveBuilder, &IArchiveBuilder::valueChanged, &dialog, &QProgressDialog::setValue);
		qDebug() << "Beginning async marking operation";
		this->m_ArchiveBuilder->setShareData(true);
		QFuture<uint32_t> future = QtConcurrent::run(this->m_ArchiveBuilder, &IArchiveBuilder::setFiles);
		futureWatcher.setFuture(future);
		qDebug() << "Progress dialog imminent";
		dialog.exec();
		qDebug() << "Waiting for marking to complete";
		future.waitForFinished();
		auto result = future.result();
		qDebug() << "Result obtained:" << result << "files marked";
		return result;
	}
} // namespace BsaPacker
