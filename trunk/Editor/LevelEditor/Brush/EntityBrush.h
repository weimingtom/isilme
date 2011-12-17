#pragma once

#include "IBrush.h"

using namespace System;
using namespace Common;

namespace LevelEditor
{
	namespace Brush
	{
		public ref class EntityBrush : public IBrush
		{
		public:
			EntityBrush(CommandManager^ commandManager);

			virtual ~EntityBrush();

			virtual void OnMouseUp(int x, int y);

			virtual void OnMouseDown(int x, int y);

			virtual void OnMouseMove(int x, int y);

			property String^ EntityType
			{
				void set(String^ value);
			}
		private:
			char* mEntityType;
			CommandManager^ mCommandManager;
		};
	}
}