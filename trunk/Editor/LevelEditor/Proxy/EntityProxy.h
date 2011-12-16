#pragma once
using namespace Common;

#include "../Stdafx.h"
#include "../SharedCLIPtr.h"

namespace LevelEditor
{
	namespace Proxy
	{
		public ref class EntityProxy : public ProxyObject
		{
		public:
			EntityProxy(EntityPtr entity);
			virtual ~EntityProxy();

			property float PositionX
			{
				float get()
				{
					return mEntity->Value->GetPosition().x;
				}
				void set(float value)
				{
					float y = mEntity->Value->GetPosition().y;
					mEntity->Value->SetPosition(value, y);
				}
			}
		private:
			SharedCLIPtr<Entity>* mEntity;
		};
	}
}