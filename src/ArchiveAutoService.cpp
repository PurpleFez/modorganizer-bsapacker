#include <bsapacker/ArchiveAutoService.h>

namespace BsaPacker
{
	void ArchiveAutoService::CreateBSA(libbsarch::bs_archive_auto* archive, const QString& archiveName) const
	{
		archive->save_to_disk(archiveName.toStdString());
	}
} // namespace BsaPacker
