#ifndef IDUMMYPLUGINLOGIC_H
#define IDUMMYPLUGINLOGIC_H

#include <string>

namespace BsaPacker
{
	class IDummyPluginLogic
	{
	public:
		virtual ~IDummyPluginLogic() = default;
		[[nodiscard]] virtual bool canCreateDummyESP(const std::string& fileNameNoExtension) const = 0;
		[[nodiscard]] virtual bool canCreateDummyESL(const std::string& fileNameNoExtension) const = 0;
	};
}

#endif // IDUMMYPLUGINLOGIC_H
