#include "src/QBSArchiveAuto.h"

namespace BsaPacker
{
	QBSArchiveAuto::QBSArchiveAuto(const bsa_archive_type_t &type) : bs_archive(type)
	{
	}

	void QBSArchiveAuto::cancel()
	{
		this->cancelled = true;
	}

	void QBSArchiveAuto::add_file_from_disk(const libbsarch::disk_blob &blob)
	{
		files_.emplace_back(blob);
	}

	void QBSArchiveAuto::save_to_disk(const libbsarch::convertible_string &archive_path)
	{
		for (const auto &file : files_)
			entries_.add(file.path_in_archive);

		bs_archive::create(archive_path, entries_);

		for (const auto &file : files_)
		{
			if (this->cancelled) {
				return;
			}
			switch (file.data.index())
			{
				case 0:
				{
					const auto &blob = std::get<libbsarch::memory_blob>(file.data);
					bs_archive::add_file_from_memory(file.path_in_archive, blob);
					break;
				}
				case 1:
				{
					const auto &file_path = std::get<libbsarch::convertible_string>(file.data);
					const auto &blob = libbsarch::disk_blob(file.path_in_archive, file_path, bool());
					bs_archive::add_file_from_disk(blob);
				}
			}
		}
		bs_archive::save();
	}
}