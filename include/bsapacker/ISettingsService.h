#ifndef ISETTINGSSERVICE_H
#define ISETTINGSSERVICE_H

#include <QList>

namespace BsaPacker
{
	class ISettingsService
	{
	public:
		virtual ~ISettingsService() = default;
		[[nodiscard]] virtual QVariant GetPluginSetting(const QString&) const = 0;
	};
}

#endif // ISETTINGSSERVICE_H
