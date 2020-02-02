#include <bsapacker/ArchiveAutoService.h>

#include <QDebug>

namespace BsaPacker
{
	void ArchiveAutoService::CreateBSA(libbsarch::bs_archive_auto* archive, const QString& archiveName) const
	{
		qDebug() << "Saving archive " + archiveName + " to disk";
		archive->save_to_disk(archiveName.toStdString());
		qDebug() << "Finished writing archive " + archiveName + " to disk";
	}
} // namespace BsaPacker
