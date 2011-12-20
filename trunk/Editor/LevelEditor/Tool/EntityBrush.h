#pragma once

#include "ITool.h"
#include "Tool.h"
#include "../SharedCLIPtr.h"

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



			property float Angle
			{
				float get();
				void set(float value);
			}
		private:
			SharedCLIPtr<Entity>* mTempEntity;
			float mDefaultAngle;
			char* mEntityType;
			Common::CommandManager^ mCommandManager;
		};
	}
}