#ifndef ARCHIVEAUTOSERVICE_H
#define ARCHIVEAUTOSERVICE_H

#include <bsapacker/IArchiveAutoService.h>

namespace BsaPacker
{
	class ArchiveAutoService : public IArchiveAutoService
	{
	public:
		ArchiveAutoService() = default;
		~ArchiveAutoService() override = default;
		ArchiveAutoService(const ArchiveAutoService&) = delete;
		ArchiveAutoService& operator=(const ArchiveAutoService&) = delete;
		ArchiveAutoService(ArchiveAutoService&&) = default;
		ArchiveAutoService& operator=(ArchiveAutoService&&) = default;

		void CreateBSA(libbsarch::bs_archive_auto* archive, const QString& archiveName) const override;
	};
} // namespace BsaPacker

#endif // ARCHIVEAUTOSERVICE_H
