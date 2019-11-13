#ifndef IPACKERPROGRESSDIALOG_H
#define IPACKERPROGRESSDIALOG_H

#include <QProgressDialog>


namespace BsaPacker
{
	class IPackerProgressDialog : public QProgressDialog
	{
		Q_OBJECT

	public:
		virtual ~IPackerProgressDialog() override = default;
	};
} // namespace BsaPacker

Q_DECLARE_INTERFACE(BsaPacker::IPackerProgressDialog, "IPackerProgressDialog")

#endif // IPACKERPROGRESSDIALOG_H
