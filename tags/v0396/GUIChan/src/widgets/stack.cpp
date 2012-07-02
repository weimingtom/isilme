#include "guichan/widgets/stack.hpp"
#include <cmath>

namespace gcn
{
	Stack::Stack() : 
		mSpacing(1),
		mOrientation(OrientationVertical)
	{

	}

	Stack::~Stack()
	{

	}

	void Stack::AddChild( WidgetPtr child )
	{
		int x = 0;
		int y = 0;
		if (mWidgets.size() > 0)
		{
			WidgetPtr last = mWidgets.back();
			if (mOrientation == OrientationVertical)
			{
				y = last->GetY() + last->GetHeight() + mSpacing;
			}
			else
			{
				x = last->GetX() + last->GetWidth() + mSpacing;
			}
		}
		child->SetPosition(x, y);

		BasicContainer::Add(child);

		if (mOrientation == OrientationVertical)
		{
			SetSize(std::max(GetWidth(), child->GetWidth()), y + child->GetHeight());
		}
		else
		{
			SetSize(x + child->GetWidth(), std::max(GetHeight(), child->GetHeight()));
		}
	}

	void Stack::SetSpacing( int spacing )
	{
		if (mSpacing != spacing)
		{
			mSpacing = spacing;
			RebuildLayout();
		}
	}

	int Stack::GetSpacing() const
	{
		return mSpacing;
	}

	void Stack::Draw( GraphicsPtr graphics )
	{
		//if (IsOpaque())
		//{
		//	graphics->setColor(getBaseColor());
		//	graphics->fillRectangle(Rectangle(0, 0, GetWidth(), GetHeight()));
		//}

		DrawChildren(graphics);
	}

	gcn::StackPtr Stack::Create()
	{
		StackPtr s(new Stack());
		return s;
	}

	Stack::Orientation Stack::GetOrientation() const
	{
		return mOrientation;
	}

	void Stack::SetOrientation( Stack::Orientation orientation /*= OrientationVertical*/ )
	{
		if (mOrientation != orientation)
		{
			mOrientation = orientation;
			RebuildLayout();
		}

	}

	void Stack::RebuildLayout()
	{
		int x = 0;
		int y = 0;
		int w = 0;
		int h = 0;
		for (WidgetListIterator it = mWidgets.begin(); it != mWidgets.end(); ++it)
		{
			WidgetPtr child = *it;
			child->SetPosition(x, y);
			if (mOrientation == OrientationVertical)
			{
				y = y + child->GetHeight() + mSpacing;
			}
			else
			{
				x = x + child->GetWidth() + mSpacing;
			}
			w = std::max(child->GetWidth(), w);
			h = std::max(child->GetHeight(), h);
		}
		w = std::max(w, x - mSpacing);
		SetSize(w, std::max(h, y - mSpacing));
	}

	void Stack::RemoveChild( WidgetPtr child )
	{
		BasicContainer::Remove(child);
		RebuildLayout();
	}

}