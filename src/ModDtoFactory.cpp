#include <bsapacker/ModDtoFactory.h>

#include "ModDto.h"
#include "NullModDto.h"
#include "PackerDialog.h"
#include <QInputDialog>
#include <QMessageBox>

namespace BsaPacker
{
	const uint16_t FALLOUT_4_NEXUS_ID = 1151;
	const QString& VALIDATOR_MSG = QObject::tr("Archive name (no file extension):");
	const QString& FILE_MSG = QObject::tr("File \"");
	const QString& ALREADYEXISTS_MSG = QObject::tr("\" already exists. Overwrite?");

	ModDtoFactory::ModDtoFactory(const IModContext* modContext)
		: m_ModContext(modContext)
	{
	}

	std::unique_ptr<IModDto> ModDtoFactory::Create() const
	{
		PackerDialog packerDialog(this->m_ModContext);
		packerDialog.RefreshModList();
		int result = packerDialog.exec();
		if (result != QDialog::DialogCode::Accepted)
		{
			return std::make_unique<NullModDto>();
		}

		const int nexusId = this->m_ModContext->GetNexusId();
		const QString& modName = packerDialog.SelectedMod();
		const QString& modDir = this->m_ModContext->GetAbsoluteModPath(modName);
		const QString& pluginName = packerDialog.SelectedPluginItem();
		const QString& archiveName = ModDtoFactory::ArchiveNameValidator(modName, pluginName);
		const QString& archiveExtension = nexusId == FALLOUT_4_NEXUS_ID
				? QStringLiteral(".ba2")
				: QStringLiteral(".bsa");

		auto dto = std::make_unique<ModDto>(nexusId, modDir, archiveName, archiveExtension);
		Q_EMIT this->onCreated(dto.get());
		return dto;
	}

	QString ModDtoFactory::ArchiveNameValidator(const QString& modName, const QString& pluginName)
	{
		QString archive_name_base;
		// check if it is the "new filename" text
		const bool needsNewName = !static_cast<bool>(QString::compare(pluginName.chopped(4), QStringLiteral("<new filename>")));
		if (needsNewName) {
			bool ok = false;
			const QString& name = QInputDialog::getText(nullptr,
														QStringLiteral("BSA Packer"),
														VALIDATOR_MSG,
														QLineEdit::Normal,
														modName,
														&ok).simplified();
			if (!ok || name.isEmpty() || name.isNull()) {
				return nullptr;
			}
			archive_name_base = name;
		} else {
			archive_name_base = pluginName.chopped(4); // trims the file extension off
		}
		return archive_name_base;
	}

	bool ModDtoFactory::CanOverwriteFile(const QString& filePath, const QString& fileName)
	{
		const QString& absoluteFileName = filePath + '/' + fileName;
		const QFileInfo& fileInfo(absoluteFileName);
		if (!fileInfo.exists() || !fileInfo.isFile()) {
			return true;
		}

		const QString& message = FILE_MSG + absoluteFileName + ALREADYEXISTS_MSG;
		return QMessageBox::question(nullptr, QStringLiteral("BSA Packer"), message, QMessageBox::Ok | QMessageBox::Cancel) != QMessageBox::Cancel;
	}
} // namespace BsaPacker
