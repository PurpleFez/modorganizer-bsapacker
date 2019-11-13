#include <bsapacker/PackerProgressDialogFactory.h>

#include "PackerProgressDialog.h"

namespace BsaPacker
{
	std::unique_ptr<IPackerProgressDialog> PackerProgressDialogFactory::Create() const
	{
		return std::make_unique<PackerProgressDialog>();
	}
}
