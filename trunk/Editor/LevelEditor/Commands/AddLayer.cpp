#include "Stdafx.h"
#include "AddLayer.h"
#include "../Proxy/LayerProxy.h"
#include "../Proxy/LevelProxy.h"

namespace LevelEditor
{
namespace Commands
{
	AddLayer::AddLayer( LevelProxy^ level, LayerProxy^ layer )
	{
		mLayer = layer;
		mLevel = level;
	}

	void AddLayer::Execute()
	{
		mLevel->AddLayer(mLayer);
	}

	void AddLayer::Unexecute()
	{
		mLevel->RemoveLayer(mLayer);
	}

}
}