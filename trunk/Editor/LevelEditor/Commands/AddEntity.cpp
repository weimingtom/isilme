#include "StdAfx.h"
#include "AddEntity.h"

namespace LevelEditor
{
	namespace Commands
	{
		AddEntity::AddEntity( LayerPtr layer, EntityPtr entity )
		{
			mLayer = new SharedCLIPtr<Layer>(layer);
			mEntity = new SharedCLIPtr<Entity>(entity);
		}

		void AddEntity::Execute()
		{
			mLayer->Value->Add(mEntity->Value);
		}

		void AddEntity::Unexecute()
		{
			mLayer->Value->Remove(mEntity->Value);
		}

		AddEntity::~AddEntity()
		{
			delete mLayer;
			delete mEntity;
		}


	}

}
