#pragma once

#include "ITool.h"
#include "../Proxy/LayerProxy.h"
#include "Tool.h"

using namespace System;
using namespace Common;
using namespace LevelEditor::Proxy;

namespace LevelEditor
{
	namespace Tool
	{
		public ref class SelectorTool : public LayerTool
		{
		public:
			SelectorTool(Common::CommandManager^ commandManager);

			virtual ~SelectorTool();

			virtual void OnMouseUp(MouseData^ mouse) override;

			virtual void OnMouseDown(MouseData^ mouse) override;

			virtual void OnMouseMove(MouseData^ mouse) override;

		private:
			EntityProxy^ GetEntity(MouseData^ mouse);
			bool isMoving;
			Common::CommandManager^ mCommandManager;

			LayerProxy^ mLayer;
		};
	}
}