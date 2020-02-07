#ifndef DUMMYPLUGINLOGIC_H
#define DUMMYPLUGINLOGIC_H

#include <bsapacker/IDummyPluginLogic.h>
#include <bsapacker/ISettingsService.h>
#include <bsapacker/IArchiveNameService.h>
#include <array>

namespace BsaPacker
{
	class DummyPluginLogic : public IDummyPluginLogic
	{
	public:
		DummyPluginLogic(const ISettingsService* settingsService,
						 const IArchiveNameService* archiveNameService);
		~DummyPluginLogic() override = default;
		[[nodiscard]] bool canCreateDummyESP(const std::string& fileNameNoExtension) const override;
		[[nodiscard]] bool canCreateDummyESL(const std::string& fileNameNoExtension) const override;

	private:
		template<std::size_t SIZE>
		bool canCreateDummy(const std::array<std::string, SIZE>& fileList,	const std::string& fileNameNoExtension) const;

		const ISettingsService* m_SettingsService = nullptr;
		const IArchiveNameService* m_ArchiveNameService = nullptr;
	};
}

#endif // DUMMYPLUGINLOGIC_H
