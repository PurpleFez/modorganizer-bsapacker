#ifndef IMODDTOPROCESSSERVICE_H
#define IMODDTOPROCESSSERVICE_H

#include <QObject>
#include "IModDto.h"

namespace BsaPacker
{
	class IModDtoProcessService : public QObject
	{
		Q_OBJECT

	public:
		virtual ~IModDtoProcessService() = default;

	public Q_SLOTS:
		virtual void Process(const IModDto*) const = 0;
	};
} // namespace BsaPacker

Q_DECLARE_INTERFACE(BsaPacker::IModDtoProcessService, "com.PurpleFez.BSA_Packer/1.0");

#endif // IMODDTOPROCESSSERVICE_H
