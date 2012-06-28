#ifndef ISILME_INVENTORY_GUI_TYPES_H
#define ISILME_INVENTORY_GUI_TYPES_H

#include "../Types.h"

namespace gcn
{
	class ItemView;
	typedef boost::shared_ptr<ItemView> ItemViewPtr;

	class InventoryView;
	typedef boost::shared_ptr<InventoryView> InventoryViewPtr;

	class InventoryWindow;
	typedef boost::shared_ptr<InventoryWindow> InventoryWindowPtr;
}
#endif