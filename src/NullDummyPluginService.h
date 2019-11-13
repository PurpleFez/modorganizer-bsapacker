#ifndef NULLDUMMYPLUGINSERVICE_H
#define NULLDUMMYPLUGINSERVICE_H

#include <bsapacker/IDummyPluginService.h>

namespace BsaPacker
{
	class NullDummyPluginService : public IDummyPluginService
	{
	public:
		NullDummyPluginService() = default;
		~NullDummyPluginService() override = default;
		bool CreatePlugin(const QString& mod_path, const QString& archive_name_base) const override;
	};
}

#endif // NULLDUMMYPLUGINSERVICE_H
