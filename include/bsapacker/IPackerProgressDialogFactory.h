#ifndef IPACKERPROGRESSDIALOGFACTORY_H
#define IPACKERPROGRESSDIALOGFACTORY_H

#include <bsapacker/IPackerProgressDialog.h>

namespace BsaPacker
{
	class IPackerProgressDialogFactory
	{
	public:
		virtual ~IPackerProgressDialogFactory() = default;
		virtual std::unique_ptr<IPackerProgressDialog> Create() const = 0;
	};
}

#endif // IPACKERPROGRESSDIALOGFACTORY_H
