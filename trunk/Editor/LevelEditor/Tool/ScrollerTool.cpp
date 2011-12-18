#include "Stdafx.h"
#include "ScrollerTool.h"
#include "../Proxy/LevelProxy.h"
#include "MouseData.h"

namespace LevelEditor
{
	namespace Tool
	{
	

		ScrollerTool::ScrollerTool()
		{

		}

		void ScrollerTool::OnMouseDown( MouseData^ mouse )
		{
			if (Level != nullptr && mouse->button ==  MouseKey::MiddleButton)
			{
				mOldX = mouse->x;
				mOldY = mouse->y;
			}
		}

		void ScrollerTool::OnMouseUp( MouseData^ mouse )
		{
			if (Level != nullptr && mouse->button ==  MouseKey::MiddleButton)
			{
				OnMouseMove(mouse);
			}
		}

		void ScrollerTool::OnMouseMove( MouseData^ mouse )
		{
			if (Level != nullptr && mouse->button ==  MouseKey::MiddleButton)
			{
				float dx = mOldX - mouse->x;
				float dy = mOldY - mouse->y;

				dx /= 64.0f;
				dy /= 64.0f;

				Level->mLevel->Value->GetActiveCamera()->x += dx;
				Level->mLevel->Value->GetActiveCamera()->y += dy;

				mOldX = mouse->x;
				mOldY = mouse->y;
			}
		}

		LevelProxy^ ScrollerTool::Level::get()
		{
			return mLevel;
		}

		void ScrollerTool::Level::set(LevelProxy^ value)
		{
			mLevel = value;
		}
	}
}