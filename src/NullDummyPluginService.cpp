#include "NullDummyPluginService.h"

namespace BsaPacker
{
	bool NullDummyPluginService::CreatePlugin(const QString& mod_path, const QString& archive_name_base) const
	{
		return false;
	}
}
