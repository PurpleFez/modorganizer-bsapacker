#ifndef MODDTOFACTORY_H
#define MODDTOFACTORY_H

#include <bsapacker/IModDtoFactory.h>
#include <bsapacker/IModContext.h>

namespace BsaPacker
{
	class ModDtoFactory : public IModDtoFactory
	{
		Q_OBJECT
			Q_INTERFACES(BsaPacker::IModDtoFactory)

	public:
		ModDtoFactory(const IModContext* modContext);
		~ModDtoFactory() override = default;
		ModDtoFactory(const ModDtoFactory&) = default;
		ModDtoFactory& operator=(const ModDtoFactory&) = default;
		ModDtoFactory(ModDtoFactory&&) = default;
		ModDtoFactory& operator=(ModDtoFactory&&) = default;

		[[nodiscard]] std::unique_ptr<IModDto> Create() const override;
		[[nodiscard]] static QString ArchiveNameValidator(const QString& modName, const QString& pluginName);
		[[nodiscard]] static bool CanOverwriteFile(const QString& filePath, const QString& fileName);

	Q_SIGNALS:
		void onCreated(const IModDto*) const;

	private:
		const IModContext* m_ModContext = nullptr;
	};
} // namespace BsaPacker

#endif // MODDTOFACTORY_H
