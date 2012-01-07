#ifndef ISILME_GUI_MODALDIALOG_H
#define ISILME_GUI_MODALDIALOG_H

#include "Definitions.h"

namespace gcn
{
	class ISILME_API ModalDialog : public Window
	{
	public:
		ModalDialog();
		virtual ~ModalDialog();

		virtual void Close();

		void Show(gcn::Container* container);

		//boost::signal<void(ModalDialog*)> OnClosed;
	private:
		Container* mContainer;
	};
};

#endif