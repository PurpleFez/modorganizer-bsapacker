#ifndef IARCHIVEEXTENSIONSERVICE_H
#define IARCHIVEEXTENSIONSERVICE_H

#include <QString>

namespace BsaPacker
{
	class IArchiveExtensionService
	{
	public:
		virtual ~IArchiveExtensionService() = default;
		virtual QString GetFileExtension() const = 0;
	};
}

#endif // IARCHIVEEXTENSIONSERVICE_H
