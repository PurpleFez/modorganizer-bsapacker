#include <bsapacker/ArchiveBuildDirector.h>

#include <QProgressDialog>

namespace BsaPacker
{
	ArchiveBuildDirector::ArchiveBuildDirector(
			IArchiveBuilder* archiveFileBuildService)
		: m_ArchiveFileBuildService(archiveFileBuildService)
	{
	}

	uint32_t ArchiveBuildDirector::Construct()
	{
		QProgressDialog dialog("Adding to archive",
							   "Abort",
							   0,
							   static_cast<int>(this->m_ArchiveFileBuildService->getFileCount()));
		QObject::connect(&dialog, &QProgressDialog::canceled, this->m_ArchiveFileBuildService, &IArchiveBuilder::cancel);
		QObject::connect(this->m_ArchiveFileBuildService, SIGNAL(valueChanged(int)), &dialog, SLOT(setValue(int)));
		dialog.show();
		this->m_ArchiveFileBuildService->setShareData(true);
		uint32_t count = this->m_ArchiveFileBuildService->setFiles();
		dialog.close();
		return count;
	}
} // namespace BsaPacker
