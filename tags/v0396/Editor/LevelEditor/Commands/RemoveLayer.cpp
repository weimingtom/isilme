#include "Stdafx.h"
#include "RemoveLayer.h"
#include "../Proxy/LayerProxy.h"
#include "../Proxy/LevelProxy.h"

namespace LevelEditor
{
	namespace Commands
	{
		RemoveLayer::RemoveLayer( LevelProxy^ level, LayerProxy^ layer )
		{
			mLayer = layer;
			mLevel = level;
		}

		void RemoveLayer::Execute()
		{
			mLevel->RemoveLayer(mLayer);
		}

		void RemoveLayer::Unexecute()
		{
			mLevel->AddLayer(mLayer);
		}

	}
}