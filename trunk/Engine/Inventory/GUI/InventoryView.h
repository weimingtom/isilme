#ifndef ISILME_INVENTORY_GUI_INVENTORYVIEW_H
#define ISILME_INVENTORY_GUI_INVENTORYVIEW_H

#include "Types.h"
#include "guichan/widgets/stack.hpp"

namespace gcn
{
	class ISILME_API InventoryView : public Stack
	{
	public:
		static InventoryViewPtr Create(inventory::InventoryPtr inv, int width = 200, int height = 300);

		InventoryView();
		virtual ~InventoryView();

		virtual void Init(inventory::InventoryPtr inv, int width, int height );

		inventory::InventoryPtr GetData() const;

		void SetData(inventory::InventoryPtr data);
	private:
		inventory::InventoryPtr mData;

		ListViewPtr mInvList;

		void OnItemAdded(inventory::ItemPtr item);
		void OnItemRemoved(inventory::ItemPtr item);

		std::map<inventory::ItemPtr, WidgetPtr> mWidgetMap;
	};
}
#endif