#include "guichan/widgets/ListView.hpp"
#include "guichan/widgets/stack.hpp"

namespace gcn
{

	ListViewPtr ListView::Create()
	{
		ListViewPtr lv(new ListView());
		lv->Init();
		return lv;
	}

	ListView::ListView()
	{

	}

	ListView::~ListView()
	{

	}

	void ListView::AddItem( WidgetPtr child )
	{
		mItemsStack->AddChild(child);
	}

	void ListView::Init()
	{
		mItemsStack = Stack::Create();
		SetContent(mItemsStack);
	}

	WidgetPtr ListView::GetItem( int i ) const
	{
		return WidgetPtr();
	}

	int ListView::GetSize() const
	{
		return 0;
	}

	void ListView::RemoveItem( WidgetPtr child )
	{
		mItemsStack->RemoveChild(child);
	}

}