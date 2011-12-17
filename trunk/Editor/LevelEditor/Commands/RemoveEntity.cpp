#include "Stdafx.h"
#include "RemoveEntity.h"
#include "../Proxy/LayerProxy.h"
#include "../Proxy/EntityProxy.h"

namespace LevelEditor
{
	namespace Commands
	{
		RemoveEntity::RemoveEntity(LayerProxy^ layer, EntityProxy^ entity )
		{
			mLayer = layer;
			mEntity = entity;
		}

		void RemoveEntity::Execute()
		{
			mLayer->RemoveEntity(mEntity);
		}

		void RemoveEntity::Unexecute()
		{
			mLayer->AddEntity(mEntity);
		}
	}
}