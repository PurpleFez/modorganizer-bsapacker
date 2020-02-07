#include "NewVegasDummyPluginService.h"

#include <QMessageBox>

namespace BsaPacker
{
	NewVegasDummyPluginService::NewVegasDummyPluginService(
			const IFileWriterService* fileWriterService,
			const IDummyPluginLogic* dummyPluginLogic)
		: m_FileWriterService(fileWriterService),
		  m_DummyPluginLogic(dummyPluginLogic)
	{
	}

	bool NewVegasDummyPluginService::CreatePlugin(const std::string& modPath, const std::string& archiveNameBase) const
	{
		const std::string& absoluteFileNameNoExtension = modPath + '/' + archiveNameBase;
		if (!this->m_DummyPluginLogic->canCreateDummyESP(absoluteFileNameNoExtension))
		{
			return false;
		}
		const std::string& absoluteFileName = absoluteFileNameNoExtension + ".esp";
		return this->m_FileWriterService->Write(absoluteFileName,
												reinterpret_cast<const char*>(NewVegasDummyPluginService::RAW_NEWVEGAS),
												sizeof(NewVegasDummyPluginService::RAW_NEWVEGAS));
	}
}

