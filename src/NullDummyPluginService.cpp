#include "NullDummyPluginService.h"

namespace BsaPacker
{
	bool NullDummyPluginService::CreatePlugin(const QString& modPath, const QString& archiveNameBase) const
	{
		return false;
	}
}
