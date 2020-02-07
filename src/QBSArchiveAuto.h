#ifndef QBSARCHIVEAUTO_H
#define QBSARCHIVEAUTO_H

#include "bs_archive.h"
#include <QObject>

namespace BsaPacker
{
	class QBSArchiveAuto : public QObject, public libbsarch::bs_archive
	{
		Q_OBJECT

	public:
		QBSArchiveAuto(const bsa_archive_type_t &type);
		~QBSArchiveAuto() = default;

		void add_file_from_disk(const libbsarch::disk_blob &blob) override;
		void save_to_disk(const libbsarch::convertible_string &archive_path);

	public Q_SLOTS:
		void cancel();

	protected:
		libbsarch::bs_archive_entries entries_;

	private:
		using bs_archive::create; //Use save_to_disk instead
		using bs_archive::save;   //Use save_to_disk instead
		std::vector<libbsarch::bs_packed_file> files_;
		bool cancelled = false;
	};
} // namespace BsaPacker


#endif // QBSARCHIVEAUTO_H