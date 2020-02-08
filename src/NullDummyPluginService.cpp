#include "NullDummyPluginService.h"

namespace BsaPacker
{
	bool NullDummyPluginService::CreatePlugin(const std::string& modPath, const std::string& archiveNameBase) const
	{
		return false;
	}
}
