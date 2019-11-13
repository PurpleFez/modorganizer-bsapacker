#include "PackerProgressDialog.h"

namespace BsaPacker
{
	PackerProgressDialog::PackerProgressDialog(QWidget *parent)
	{
		this->setLabelText("Counting files.");
		this->setCancelButtonText("Abort");
		this->setMinimum(0);
		this->setMaximum(0);
		this->setParent(parent);
		//this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
	}
} // namespace BsaPacker
