#ifndef ARCHIVEBUILDERFACTORY_H
#define ARCHIVEBUILDERFACTORY_H

#include "bsapacker_global.h"
#include <bsapacker/IArchiveBuilderFactory.h>
#include <bsapacker/IArchiveBuilder.h>
#include <bsapacker/IArchiveBuilderHelper.h>
#include <bsapacker/IModDto.h>
#include <bs_archive_auto.hpp>

namespace BsaPacker
{
	class BSAPACKER_EXPORT ArchiveBuilderFactory : public IArchiveBuilderFactory
	{
	public:
		ArchiveBuilderFactory(const IArchiveBuilderHelper* archiveBuilderHelper);
		~ArchiveBuilderFactory() override = default;
		ArchiveBuilderFactory(const ArchiveBuilderFactory&) = delete;
		ArchiveBuilderFactory& operator=(const ArchiveBuilderFactory&) = delete;
		ArchiveBuilderFactory(ArchiveBuilderFactory&&) = delete;
		ArchiveBuilderFactory& operator=(ArchiveBuilderFactory&&) = delete;

		[[nodiscard]] std::vector<bsa_archive_type_t> GetArchiveTypes(const IModDto* modDto) const override;
		[[nodiscard]] std::unique_ptr<IArchiveBuilder> Create(bsa_archive_type_t archiveType, const IModDto* modDto) const override;

	private:
		const IArchiveBuilderHelper* m_ArchiveBuilderHelper = nullptr;
	};
} // namespace BsaPacker

#endif // ARCHIVEBUILDERFACTORY_H
