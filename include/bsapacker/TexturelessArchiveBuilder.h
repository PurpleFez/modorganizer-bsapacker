#ifndef TEXTURELESSARCHIVEBUILDER_H
#define TEXTURELESSARCHIVEBUILDER_H

#include <bsapacker/IArchiveBuilder.h>
#include <bsapacker/IArchiveBuilderHelper.h>
#include <QObject>

namespace BsaPacker
{
	class TexturelessArchiveBuilder : public IArchiveBuilder
	{
		Q_OBJECT
			Q_INTERFACES(BsaPacker::IEmitsValueChanged)

	public:
		explicit TexturelessArchiveBuilder(const IArchiveBuilderHelper* archiveBuilderHelper, const QDir& rootDir);
		//TexturelessArchiveBuilder(const TexturelessArchiveBuilder&) = delete;
		//TexturelessArchiveBuilder(const TexturelessArchiveBuilder&&) = delete;
		~TexturelessArchiveBuilder() override = default;
		uint32_t setFiles() override;
		void setShareData(bool) override;
		//void setExtensionBlacklist(const QStringList&) override;

		[[nodiscard]] std::unique_ptr<BSArchiveAuto> getArchive() override;
		[[nodiscard]] uint32_t getFileCount() const override;

		// IEmitsValueChanged interface
	public Q_SLOTS:
		void cancel() override;

	signals:
		void valueChanged(int) override;

	private:
		const IArchiveBuilderHelper* m_ArchiveBuilderHelper = nullptr;
		std::unique_ptr<BSArchiveAuto> m_Archive;
		bool m_Cancelled;
		QDir m_RootDirectory;
	};
} // namespace BsaPacker

#endif // TEXTURELESSARCHIVEBUILDER_H
