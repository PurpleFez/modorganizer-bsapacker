#ifndef MODDTOFACTORY_H
#define MODDTOFACTORY_H

#include <bsapacker/IModDtoFactory.h>
#include <bsapacker/IModContext.h>
#include <bsapacker/IModDto.h>

#include <boost/di.hpp>
#include <boost/di/extension/injections/factory.hpp>

namespace di = boost::di;
namespace BsaPacker
{
	class ModDtoFactory : public IModDtoFactory
	{
	public:
		ModDtoFactory(const IModContext* modContext);
		~ModDtoFactory() override = default;
		// IModDtoFactory interface
		[[nodiscard]] std::unique_ptr<IModDto> Create() const override;
		//static std::unique_ptr<IModDto> Create(const IModContext*);
		static QString ArchiveNameValidator(const QString& modName, const QString& pluginName);

	private:
		const IModContext* m_ModContext = nullptr;
	};
} // namespace BsaPacker
#endif // MODDTOFACTORY_H
