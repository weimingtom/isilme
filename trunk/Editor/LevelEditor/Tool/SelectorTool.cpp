#include "Stdafx.h"
#include "SelectorTool.h"
#include "../Proxy/EntityProxy.h"
#include "../Proxy/LayerProxy.h"

using namespace System;
using namespace Common;

namespace LevelEditor
{
	namespace Tool
	{


		SelectorTool::SelectorTool( CommandManager^ commandManager )
		{

		}

		SelectorTool::~SelectorTool()
		{

		}

		void SelectorTool::OnMouseUp( MouseData^ mouse )
		{
			if (Layer != nullptr)
			{
				for each (EntityProxy^ entity in Layer->Entities)
				{
					
				}
			}
		}

		void SelectorTool::OnMouseDown( MouseData^ mouse )
		{

		}

		void SelectorTool::OnMouseMove( MouseData^ mouse )
		{

		}

	}
}