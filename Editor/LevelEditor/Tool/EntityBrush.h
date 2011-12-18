#pragma once

#include "ITool.h"
#include "Tool.h"
using namespace System;
using namespace Common;

namespace LevelEditor
{
	namespace Tool
	{
		public ref class EntityBrush : public LayerTool
		{
		public:
			EntityBrush(Common::CommandManager^ commandManager);

			virtual ~EntityBrush();

			virtual void OnMouseUp(MouseData^ mouse) override;

			virtual void OnMouseDown(MouseData^ mouse) override;

			virtual void OnMouseMove(MouseData^ mouse) override;

			property String^ EntityType
			{
				void set(String^ value);
			}

			property bool UseGrid
			{
				bool get();
				void set(bool value);
			}
		private:
			bool mUseGrid;
			float mDefaultAngle;
			char* mEntityType;
			Common::CommandManager^ mCommandManager;
		};
	}
}