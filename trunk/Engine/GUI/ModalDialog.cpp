#include "IsilmePCH.h"
#include "ModalDialog.h"

namespace gcn
{
	ModalDialog::ModalDialog()
	{
	}

	ModalDialog::~ModalDialog()
	{
	}

	void ModalDialog::Close()
	{
		mContainer->remove(this);
		mContainer = 0;

		//OnClosed(this);
	}

	void ModalDialog::Show(Container* container)
	{
		mContainer = container;

		mContainer->add(this);
	}
};