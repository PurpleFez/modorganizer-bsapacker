#ifndef IFILEWRITERSERVICE_H
#define IFILEWRITERSERVICE_H

#include <string>

namespace BsaPacker
{
	class IFileWriterService
	{
	public:
		virtual ~IFileWriterService() = default;
		virtual bool Write(const std::string& path, const char* payload, const uint32_t size) const = 0;
	};
}

#endif // IFILEWRITERSERVICE_H
