#include "SkyrimSEDummyPluginService.h"

namespace BsaPacker
{
	SkyrimSEDummyPluginService::SkyrimSEDummyPluginService(const IFileWriterService* fileWriterService, const IDummyPluginLogic* dummyPluginLogic)
		: m_FileWriterService(fileWriterService), m_DummyPluginLogic(dummyPluginLogic)
	{
	}

	bool SkyrimSEDummyPluginService::CreatePlugin(const QString& modPath, const QString& archiveNameBase) const
	{
		const QString& fileNameNoExtension = modPath + '/' + archiveNameBase;
		if (!this->m_DummyPluginLogic->canCreateDummyESP(fileNameNoExtension))
		{
			return false;
		}
		const std::string& absoluteFileName = fileNameNoExtension.toStdString() + ".esp";
		return this->m_FileWriterService->Write(absoluteFileName, reinterpret_cast<const char*>(this->RAW_SKYRIMSE), this->RAW_SSE_SIZE);
	}
}
