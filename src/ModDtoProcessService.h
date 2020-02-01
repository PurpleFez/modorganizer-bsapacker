#ifndef MODDTOPROCESSSERVICE_H
#define MODDTOPROCESSSERVICE_H

#include <bsapacker/IModDtoProcessService.h>

namespace BsaPacker
{
	class ModDtoProcessService : public IModDtoProcessService
	{
		Q_OBJECT
			Q_INTERFACES(BsaPacker::IModDtoProcessService)

	public:
		void Process(const IModDto*) const;
	};
}

#endif // MODDTOPROCESSSERVICE_H
