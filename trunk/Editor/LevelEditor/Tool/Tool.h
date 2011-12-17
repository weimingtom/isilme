#pragma once

#include "../Stdafx.h"
#include "ITool.h"

using namespace LevelEditor::Proxy;

namespace LevelEditor
{
	namespace Tool
	{
		public ref class LayerTool : public ITool
		{
		public:

			virtual void OnMouseUp(MouseData^ mouse);

			virtual void OnMouseDown(MouseData^ mouse);

			virtual void OnMouseMove(MouseData^ mouse);

			property LayerProxy^ Layer
			{
				LayerProxy^ get();
				void set(LayerProxy^ value);
			}
		private:
			LayerProxy^ mLayer;
		};
	}
}