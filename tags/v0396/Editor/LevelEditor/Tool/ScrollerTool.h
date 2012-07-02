#pragma once
#include "../Stdafx.h"
#include "ITool.h"

using namespace LevelEditor::Proxy;

namespace LevelEditor
{
	namespace Tool
	{
		public ref class ScrollerTool : public ITool
		{
		public:
			ScrollerTool();

			property LevelProxy^ Level
			{
				LevelProxy^ get();
				void set(LevelProxy^ value);
			}

			virtual void OnMouseDown(MouseData^ mouse);
			virtual void OnMouseUp(MouseData^ mouse);
			virtual void OnMouseMove(MouseData^ mouse);
		private:
			LevelProxy^ mLevel;
			bool isScrooling;
			int mOldX;
			int mOldY;
		};
	}
}