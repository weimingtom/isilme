#ifndef ISILME_GCN_INVENTORY_WINDOW_H
#define ISILME_GCN_INVENTORY_WINDOW_H

#include "Definitions.h"

namespace gcn
{
	class InventoryWindow : public Window
	{
	public:
		InventoryWindow();
		virtual ~InventoryWindow();
	private:
	};
	typedef boost::shared_ptr<InventoryWindow> InventoryWindowPtr;
};

#endif