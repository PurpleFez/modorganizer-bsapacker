#ifndef IHIDELOOSEASSETSERVICE_H
#define IHIDELOOSEASSETSERVICE_H

#include <string>

namespace BsaPacker
{
	class IHideLooseAssetService
	{
	public:
		virtual ~IHideLooseAssetService() = default;
		virtual bool HideLooseAssets(const std::string& modDirectory) const = 0;
	};
}

#endif // IHIDELOOSEASSETSERVICE_H
