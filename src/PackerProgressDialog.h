#ifndef PACKERPROGRESSDIALOG_H
#define PACKERPROGRESSDIALOG_H

#include <bsapacker/IPackerProgressDialog.h>

namespace BsaPacker
{
	class PackerProgressDialog : public IPackerProgressDialog
	{
		Q_OBJECT
			Q_INTERFACES(BsaPacker::IPackerProgressDialog)
	public:
		explicit PackerProgressDialog(QWidget *parent = nullptr);
		~PackerProgressDialog() override = default;
	};
}

#endif // PACKERPROGRESSDIALOG_H
