#ifndef ARCHIVEBUILDDIRECTOR_H
#define ARCHIVEBUILDDIRECTOR_H

#include <bsapacker/IArchiveBuilder.h>
#include <bsapacker/ISettingsService.h>

#include <QProgressDialog>
#include <QFutureWatcher>

namespace BsaPacker
{
	class ArchiveBuildDirector
	{
	public:
		explicit ArchiveBuildDirector(IArchiveBuilder* archiveBuilder);
		~ArchiveBuildDirector() = default;
		ArchiveBuildDirector(const ArchiveBuildDirector&) = default;
		ArchiveBuildDirector& operator=(const ArchiveBuildDirector&) = default;
		ArchiveBuildDirector(ArchiveBuildDirector&&) = default;
		ArchiveBuildDirector& operator=(ArchiveBuildDirector&&) = default;

		uint32_t Construct();

	private:
		IArchiveBuilder* m_ArchiveBuilder = nullptr;
		QFutureWatcher<void> futureWatcher;
		QProgressDialog dialog;
	};
} // namespace BsaPacker

#endif // ARCHIVEBUILDDIRECTOR_H
