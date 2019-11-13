#ifndef PACKERPROGRESSDIALOGFACTORY_H
#define PACKERPROGRESSDIALOGFACTORY_H

#include "IPackerProgressDialog.h"
#include "IPackerProgressDialogFactory.h"


namespace BsaPacker
{
	class PackerProgressDialogFactory : public IPackerProgressDialogFactory
	{
	public:
		PackerProgressDialogFactory() = default;
		~PackerProgressDialogFactory() override = default;
		std::unique_ptr<IPackerProgressDialog> Create() const override;
	};
}


#endif // PACKERPROGRESSDIALOGFACTORY_H
