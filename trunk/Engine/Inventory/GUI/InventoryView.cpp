#include "IsilmePCH.h"
#include "InventoryView.h"
#include "guichan/widgets/ListView.hpp"
#include "../Inventory.h"
#include "ItemView.h"

namespace gcn
{


	InventoryView::InventoryView()
	{

	}

	InventoryView::~InventoryView()
	{

	}

	void InventoryView::Init(inventory::InventoryPtr inv, int width, int height )
	{
		mInvList = ListView::Create();
		mInvList->SetSize(width, height);
		mData = inv;
		for (int i = 0; i < inv->GetItemsCount(); ++i)
		{
			ItemViewPtr iv = ItemView::Create(inv->GetItem(i));
			mInvList->AddItem(iv);
			mWidgetMap[inv->GetItem(i)] = iv;
		}
		AddChild(mInvList);

		inv->ItemAdded.connect(boost::bind(&InventoryView::OnItemAdded, boost::shared_dynamic_cast<InventoryView>(shared_from_this()), _1));
		inv->ItemRemoved.connect(boost::bind(&InventoryView::OnItemRemoved, boost::shared_dynamic_cast<InventoryView>(shared_from_this()), _1));
	}

	inventory::InventoryPtr InventoryView::GetData() const
	{
		return mData;
	}

	void InventoryView::SetData( inventory::InventoryPtr data )
	{
		mData = data;
	}

	InventoryViewPtr InventoryView::Create( inventory::InventoryPtr inv, int width, int height )
	{
		InventoryViewPtr iv(new InventoryView());
		iv->Init(inv, width, height);
		return iv;
	}

	void InventoryView::OnItemAdded( inventory::ItemPtr item )
	{
		ItemViewPtr iv = ItemView::Create(item);
		mInvList->AddItem(iv);
		mWidgetMap[item] = iv;
	}

	void InventoryView::OnItemRemoved( inventory::ItemPtr item )
	{
		std::map<inventory::ItemPtr, WidgetPtr>::iterator it = mWidgetMap.find(item);

		mInvList->RemoveItem(it->second);
		mWidgetMap.erase(it);
	}

}