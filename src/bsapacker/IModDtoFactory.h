#ifndef IMODDTOFACTORY_H
#define IMODDTOFACTORY_H

#include "IModDto.h"
#include <memory>

namespace BsaPacker
{
	class IModDtoFactory : public QObject
	{
		Q_OBJECT

	public:
		virtual ~IModDtoFactory() = default;
		[[nodiscard]] virtual std::unique_ptr<IModDto> Create() const = 0;

	Q_SIGNALS:
		void onCreated(const IModDto*) const;
	};
} // namespace BsaPacker

Q_DECLARE_INTERFACE(BsaPacker::IModDtoFactory, "com.PurpleFez.BSA_Packer/1.0");

#endif // IMODDTOFACTORY_H
