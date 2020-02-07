#include <bsapacker/ArchiveAutoService.h>

#include <QDebug>

namespace BsaPacker
{
	void ArchiveAutoService::CreateBSA(QBSArchiveAuto* archive, const std::string& archiveName) const
	{
		qDebug() << "Saving archive " + QString::fromStdString(archiveName) + " to disk";
		archive->save_to_disk(archiveName);
		qDebug() << "Finished writing archive " + QString::fromStdString(archiveName) + " to disk";
	}
} // namespace BsaPacker
