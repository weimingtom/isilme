#include "Stdafx.h"
#include "MoveLayer.h"
#include "../Proxy/LevelProxy.h"
#include "../Proxy/LayerProxy.h"

namespace LevelEditor
{
	namespace Commands
	{


		MoveLayer::MoveLayer( LayerProxy^ layer, int position )
		{
			mLayer = layer;
			mLevel = layer->Level;
			mOldPosition = mLevel->Layers->IndexOf(layer);
			mNewPosition = position;
		}

		void MoveLayer::Execute()
		{
		}

		void MoveLayer::Unexecute()
		{

		}

	}
}