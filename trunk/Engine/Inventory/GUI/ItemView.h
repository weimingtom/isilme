#ifndef ISILME_IVENTORY_GUI_ITEM_VIEW_H
#define ISILME_IVENTORY_GUI_ITEM_VIEW_H

#include "Types.h"
#include "guichan/widgets/stack.hpp"

namespace gcn
{
	/// @class ItemView.
	class ISILME_API ItemView : public Stack
	{
	public:
		static ItemViewPtr Create(inventory::ItemPtr item);

		ItemView();
		virtual ~ItemView();

		/// Initializes this object.
		virtual void Init(inventory::ItemPtr item);

		/// Gets an item associated with ItemView data.
		///
		/// @return	The item.
		inventory::ItemPtr	GetData() const;

		/// Sets an item associated with ItemView data.
		///
		/// @param	data	The item.
		void SetData(inventory::ItemPtr data);
	private:
		/// @summary	The item icon.
		IconPtr mItemIcon;

		/// @summary	The item label.
		LabelPtr mItemLabel;

		/// @summary	Item associated with ItemView.
		inventory::ItemPtr	mData;
	};
}
#endif