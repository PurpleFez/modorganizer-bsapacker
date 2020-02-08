#ifndef IDUMMYPLUGINSERVICE_H
#define IDUMMYPLUGINSERVICE_H

#include <string>

namespace BsaPacker
{
	class IDummyPluginService
	{
	public:
		virtual ~IDummyPluginService() = default;
		virtual bool CreatePlugin(const std::string& modPath, const std::string& archiveNameBase) const = 0;
	};
}

#endif // IDUMMYPLUGINSERVICE_H
