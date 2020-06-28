#include <bsapacker/ArchiveAutoService.h>

#include <QDebug>

namespace BsaPacker
{
	void ArchiveAutoService::CreateBSA(libbsarch::bs_archive_auto* archive, const QString& archiveName, const bsa_archive_type_e type) const
	{
		archive->save_to_disk(archiveName.toStdString());
	}
} // namespace BsaPacker
