#include "StdAfx.h"
#include "AddEntity.h"
#include "../Proxy/EntityProxy.h"
#include "../Proxy/LayerProxy.h"

namespace LevelEditor
{
	namespace Commands
	{
		AddEntity::AddEntity( LayerProxy^ layer, EntityProxy^ entity )
		{
			mLayer = layer;
			mEntity = entity;
		}

		void AddEntity::Execute()
		{
			mLayer->AddEntity(mEntity);
		}

		void AddEntity::Unexecute()
		{
			mLayer->RemoveEntity(mEntity);
		}

		AddEntity::~AddEntity()
		{
			delete mLayer;
			delete mEntity;
		}


	}

}
