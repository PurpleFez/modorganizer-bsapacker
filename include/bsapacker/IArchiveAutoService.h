#ifndef IARCHIVEAUTOSERVICE_H
#define IARCHIVEAUTOSERVICE_H

//#include <bs_archive_auto.hpp>
#include "src/QBSArchiveAuto.h"
#include <string>

namespace BsaPacker
{
	class IArchiveAutoService
	{
	public:
		virtual ~IArchiveAutoService() = default;
		virtual void CreateBSA(QBSArchiveAuto*, const  std::string&) const = 0;
	};
} // namespace BsaPacker

#endif // IARCHIVEAUTOSERVICE_H
