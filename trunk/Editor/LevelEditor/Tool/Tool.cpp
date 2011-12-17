#include "Stdafx.h"
#include "Tool.h"

namespace LevelEditor
{
	namespace Tool
	{
		LayerProxy^ LayerTool::Layer::get()
		{
			return mLayer;
		}

		void LayerTool::Layer::set(LayerProxy^ value)
		{
			mLayer = value;
		}

		void LayerTool::OnMouseUp( MouseData^ mouse )
		{

		}

		void LayerTool::OnMouseDown( MouseData^ mouse )
		{

		}

		void LayerTool::OnMouseMove( MouseData^ mouse )
		{

		}

	}
}