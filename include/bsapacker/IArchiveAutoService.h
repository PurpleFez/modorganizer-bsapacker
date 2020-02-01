#ifndef IARCHIVEAUTOSERVICE_H
#define IARCHIVEAUTOSERVICE_H

#include <bs_archive_auto.hpp>
#include <QString>

namespace BsaPacker
{
	class IArchiveAutoService
	{
	public:
		virtual ~IArchiveAutoService() = default;
		virtual void CreateBSA(libbsarch::bs_archive_auto*, const QString&) const = 0;
	};
} // namespace BsaPacker

#endif // IARCHIVEAUTOSERVICE_H
