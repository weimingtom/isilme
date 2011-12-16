#include "Stdafx.h"
#include "EntityProxy.h"

namespace LevelEditor
{
	namespace Proxy
	{
		EntityProxy::EntityProxy( EntityPtr entity )
		{
			mEntity = new SharedCLIPtr<Entity>(entity);
		}

		EntityProxy::~EntityProxy()
		{
			delete mEntity;
		}

	}
}