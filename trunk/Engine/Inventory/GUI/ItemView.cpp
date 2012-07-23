#include "IsilmePCH.h"
#include "ItemView.h"
#include "../Item.h"

namespace gcn
{


	ItemView::ItemView()
	{

	}

	ItemView::~ItemView()
	{

	}

	void ItemView::Init(inventory::ItemPtr item)
	{
		SetOrientation(OrientationHorizontal);
		mItemIcon = IconPtr(new Icon(item->GetIcon()));
		mItemLabel = LabelPtr(new Label(item->GetTag()));
		mItemIcon->SetSize(32, 32);
		AddChild(mItemIcon);
		AddChild(mItemLabel);
	}

	inventory::ItemPtr ItemView::GetData() const
	{
		return mData;
	}

	void ItemView::SetData( inventory::ItemPtr data )
	{
		mData = data;
	}

	ItemViewPtr ItemView::Create(inventory::ItemPtr item)
	{
		ItemViewPtr iv(new ItemView());
		iv->Init(item);
		return iv;
	}

}