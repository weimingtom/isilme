#pragma once

#include "ITool.h"
#include "../Proxy/LayerProxy.h"

using namespace System;
using namespace Common;
using namespace LevelEditor::Proxy;

namespace LevelEditor
{
	namespace Tool
	{
		public ref class SelectorTool : public ITool
		{
		public:
			SelectorTool(CommandManager^ commandManager);

			virtual ~SelectorTool();

			virtual void OnMouseUp(MouseData^ mouse);

			virtual void OnMouseDown(MouseData^ mouse);

			virtual void OnMouseMove(MouseData^ mouse);

		private:
			CommandManager^ mCommandManager;

			LayerProxy^ mLayer;
		};
	}
}