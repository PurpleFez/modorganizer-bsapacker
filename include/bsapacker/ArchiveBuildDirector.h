#ifndef ARCHIVEBUILDDIRECTOR_H
#define ARCHIVEBUILDDIRECTOR_H

#include "ISettingsService.h"

#include <bsapacker/IArchiveBuilder.h>
#include <bsapacker/IPackerProgressDialogFactory.h>


namespace BsaPacker
{
	class ArchiveBuildDirector
	{
	public:
		explicit ArchiveBuildDirector(
				const ISettingsService* settingsService,
				IArchiveBuilder* archiveFileBuildService);
		~ArchiveBuildDirector() = default;
		void Construct();

	private:
		IArchiveBuilder* m_ArchiveFileBuildService = nullptr;
		const ISettingsService* m_SettingsService = nullptr;
	};
} // namespace BsaPacker

#endif // ARCHIVEBUILDDIRECTOR_H
