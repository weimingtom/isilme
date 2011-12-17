#include "Stdafx.h"
#include "EntityProxy.h"
#include "LayerProxy.h"

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

		LayerProxy^	EntityProxy::Layer::get()
		{
			return mLayer;
		}

		void EntityProxy::Layer::set(LayerProxy^ value)
		{
			mLayer = value;
		}

		String^ EntityProxy::Name::get()
		{
			return gcnew String(mEntity->Value->GetName().c_str());
		}
	}
}