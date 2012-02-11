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
		mContainer->Remove(shared_from_this());
		mContainer.reset();

		//OnClosed(this);
	}

	void ModalDialog::Show(ContainerPtr container)
	{
		mContainer = container;

		mContainer->Add(shared_from_this());
	}
};