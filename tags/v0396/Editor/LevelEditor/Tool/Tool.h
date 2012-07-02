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
			LayerTool();

			virtual void OnMouseUp(MouseData^ mouse);

			virtual void OnMouseDown(MouseData^ mouse);

			virtual void OnMouseMove(MouseData^ mouse);

			Proxy::Point^ ProcessToLevelCoords(MouseData^ position);

			Proxy::Point^ ProcessToLevelCoordsNoGrid(MouseData^ position);

			property LayerProxy^ Layer
			{
				LayerProxy^ get();
				void set(LayerProxy^ value);
			}

			property bool UseGrid
			{
				bool get();
				void set(bool value);
			}
		private:

			bool CanExecuteActivateGrid();
			void ExecutedActivateGrid(Object^ param);

			LayerProxy^ mLayer;
			bool mUseGrid;
		};
	}
}