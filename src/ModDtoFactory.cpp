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

	ModDtoFactory::ModDtoFactory(
		const IModContext* modContext,
		IPackerDialog* packerDialog) :
		m_ModContext(modContext),
		m_PackerDialog(packerDialog)
	{
	}

	std::unique_ptr<IModDto> ModDtoFactory::Create() const
	{
		this->m_PackerDialog->RefreshModList();
		int result = m_PackerDialog->Exec();
		if (result != QDialog::DialogCode::Accepted)
		{
			return std::make_unique<NullModDto>();
		}

		const int nexusId = this->m_ModContext->GetNexusId();
		const QString& modName = this->m_PackerDialog->SelectedMod();
		const QString& modDir = this->m_ModContext->GetAbsoluteModPath(modName);
		const QString& pluginName = this->m_PackerDialog->SelectedPluginItem();
		const bool needsNewName = this->m_PackerDialog->IsNewFilename();
		const QString& archiveName = ModDtoFactory::ArchiveNameValidator(modName, pluginName, needsNewName);
		const QString& archiveExtension = nexusId == FALLOUT_4_NEXUS_ID
				? QStringLiteral(".ba2")
				: QStringLiteral(".bsa");

		auto dto = std::make_unique<ModDto>(nexusId, modDir, archiveName, archiveExtension);
		Q_EMIT this->onCreated(dto.get());
		return dto;
	}

	QString ModDtoFactory::ArchiveNameValidator(
		const QString& modName,
		const QString& pluginName,
		const bool needsNewName)
	{
		QString archive_name_base;
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
