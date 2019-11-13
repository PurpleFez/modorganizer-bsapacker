#ifndef IDUMMYPLUGINLOGIC_H
#define IDUMMYPLUGINLOGIC_H

#include <QString>
#include <array>

namespace BsaPacker
{
	class IDummyPluginLogic
	{
	public:
		virtual ~IDummyPluginLogic() = default;
		[[nodiscard]] virtual bool canCreateDummyESP(const QString& fileNameNoExtension) const = 0;
		[[nodiscard]] virtual bool canCreateDummyESL(const QString& fileNameNoExtension) const = 0;
	};
}

#endif // IDUMMYPLUGINLOGIC_H
