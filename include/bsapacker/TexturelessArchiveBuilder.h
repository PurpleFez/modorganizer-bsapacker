#ifndef TEXTURELESSARCHIVEBUILDER_H
#define TEXTURELESSARCHIVEBUILDER_H

#include <bsapacker/IArchiveBuilder.h>
#include <bsapacker/IArchiveBuilderHelper.h>

namespace BsaPacker
{
	class TexturelessArchiveBuilder : public IArchiveBuilder
	{
		Q_OBJECT
			Q_INTERFACES(BsaPacker::IEmitsValueChanged)

	public:
		explicit TexturelessArchiveBuilder(const IArchiveBuilderHelper* archiveBuilderHelper, const QDir& rootDir, const bsa_archive_type_t);
		~TexturelessArchiveBuilder() override = default;
		TexturelessArchiveBuilder(const TexturelessArchiveBuilder&) = delete;
		TexturelessArchiveBuilder& operator=(const TexturelessArchiveBuilder&) = delete;
		TexturelessArchiveBuilder(TexturelessArchiveBuilder&&) = delete;
		TexturelessArchiveBuilder& operator=(TexturelessArchiveBuilder&&) = delete;

		uint32_t setFiles() override;
		void setShareData(bool) override;
		[[nodiscard]] std::unique_ptr<QBSArchiveAuto> getArchive() override;
		[[nodiscard]] uint32_t getFileCount() const override;
		[[nodiscard]] QString getRootPath() const override;

	public Q_SLOTS:
		void cancel() override;

	private:
		const IArchiveBuilderHelper* m_ArchiveBuilderHelper = nullptr;
		std::unique_ptr<QBSArchiveAuto> m_Archive;
		bool m_Cancelled;
		QDir m_RootDirectory;
	};
} // namespace BsaPacker

#endif // TEXTURELESSARCHIVEBUILDER_H
